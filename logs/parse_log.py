import re
import fileinput
import sys

class LineParser:
    TYPE_SENDING = 1
    TYPE_RECEIVING = 2

    def __init__(self):
        self.pattern = "(\\d{2}):(\\d{2})\\.(\\d{3}).+ID:(\\d+).+(Sending|Received) (\\d+).+(\\d{4}(?:\\.\\d{4}){3})"

    def parseLine(self, line):
        result = re.findall(self.pattern, line)

        if len(result) == 0:
            return None

        (rawMin, rawSec, rawMillis, rawID, sendRecv, content, address) = result[0]

        return {
            "type" : self.TYPE_SENDING if sendRecv == "Sending" else self.TYPE_RECEIVING,
            "content" : content,
            "timestamp" : int(rawMin) * 60_000 + int(rawSec) * 1000 + int(rawMillis),
            "address" : address,
            "id" : rawID
        }

class PacketLossReader:
    def __init__(self, filePath, timeSpan=None):
        self.id_dict = {}
        self.filePath = filePath
        self.timeSpan = timeSpan
        self.lineParser = LineParser()

    def addDataPoint(self, dataPoint):
        if not dataPoint["address"] in self.id_dict:
            self.id_dict[dataPoint["address"]] = {
                "lastContent" : -1,
                "lastMessageConfirmed" : True,
                "numLostPackages" : 0,
                "numSuccessfulPackages" : -1,
                "id" : dataPoint["id"]
            }

        if not self.id_dict[dataPoint["address"]]["lastMessageConfirmed"]:
            self.id_dict[dataPoint["address"]]["numLostPackages"] += 1
        else:
            self.id_dict[dataPoint["address"]]["numSuccessfulPackages"] += 1

        self.id_dict[dataPoint["address"]]["lastContent"] = dataPoint["content"]
        self.id_dict[dataPoint["address"]]["lastMessageConfirmed"] = False

    def confirmDataPoint(self, dataPoint):
        if dataPoint["content"] == self.id_dict[dataPoint["address"]]["lastContent"]:
            self.id_dict[dataPoint["address"]]["lastMessageConfirmed"] = True

    def parseFile(self):
        initialMessageTime = None

        with fileinput.FileInput(files=(self.filePath,)) as input:
            for line in input:
                lineResult = self.lineParser.parseLine(line)

                if lineResult:
                    if not initialMessageTime:
                        initialMessageTime = lineResult["timestamp"]

                    if self.timeSpan and lineResult["timestamp"] - initialMessageTime >= self.timeSpan:
                        break

                    if lineResult["type"] == LineParser.TYPE_SENDING:
                        self.addDataPoint(lineResult)
                    else:
                        self.confirmDataPoint(lineResult)

    def getResults(self):
        return self.id_dict

    def getFormattedResults(self):
        outputStr = ""

        for _, value in self.id_dict.items():
            outputStr += "ID " + value["id"] + ":\n"
            outputStr += "  # Successful Packages: " + str(value["numSuccessfulPackages"]) + "\n"
            outputStr += "  # Lost Packages: " + str(value["numLostPackages"]) + "\n"

        return outputStr

def parseFileFromCommandLine():
    if len(sys.argv) != 2:
        print("Specify one file to parse!")
        return

    dataParser = PacketLossReader(sys.argv[1], timeSpan=10*60*1000) # 10min in ms
    dataParser.parseFile()

    print(dataParser.getFormattedResults())

parseFileFromCommandLine()
