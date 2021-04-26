/*
 * Copyright (c) 2021, Kiel University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A MAC protocol that behaves as a transparent layer.
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 */

#ifndef TMAC_H_
#define TMAC_H_

#include "contiki.h"
#include "net/mac/mac.h"
#include "net/packetbuf.h"
#include "net/netstack.h"
#include "dev/radio.h"

#ifdef TMAC_CONF_SEND_SOFT_ACK
#define TMAC_SEND_SOFT_ACK TMAC_CONF_SEND_SOFT_ACK
#else /* TMAC_CONF_SEND_SOFT_ACK */
#define TMAC_SEND_SOFT_ACK 0
#endif /* TMAC_CONF_SEND_SOFT_ACK */

#ifdef TMAC_CONF_ACK_WAIT_TIME
#define TMAC_ACK_WAIT_TIME TMAC_CONF_ACK_WAIT_TIME
#else /* TMAC_CONF_ACK_WAIT_TIME */
#define TMAC_ACK_WAIT_TIME                      RTIMER_SECOND / 2500
#endif /* TMAC_CONF_ACK_WAIT_TIME */

#ifdef TMAC_CONF_AFTER_ACK_DETECTED_WAIT_TIME
#define TMAC_AFTER_ACK_DETECTED_WAIT_TIME TMAC_CONF_AFTER_ACK_DETECTED_WAIT_TIME
#else /* TMAC_CONF_AFTER_ACK_DETECTED_WAIT_TIME */
#define TMAC_AFTER_ACK_DETECTED_WAIT_TIME       RTIMER_SECOND / 1500
#endif /* TMAC_CONF_AFTER_ACK_DETECTED_WAIT_TIME */

#define TMAC_ACK_LEN 3

/* just a default - with LLSEC, etc */
#define TMAC_MAC_MAX_HEADER 21


extern const struct mac_driver transparentmac_driver;


#endif /* TMAC_H_ */
/**
 * @}
 * @}
 */
