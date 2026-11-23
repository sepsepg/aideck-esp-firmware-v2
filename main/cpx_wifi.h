/*
 * cpx_wifi.h
 * Elia Cereda <elia.cereda@idsia.ch>
 * Jérôme Guzzi <jerome@idsia.ch>
 * Esteban Gougeon <esteban.gougeon@greenwaves-technologies.com>
 * Germain Haugou <germain.haugou@greenwaves-technologies.com>
 *
 * Copyright (C) 2022-2025 IDSIA, USI-SUPSI
 * Copyright (C) 2020 Bitcraze AB
 * Copyright (C) 2019 GreenWaves Technologies
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * This software is based on the following publication:
 *    E. Cereda, A. Giusti, D. Palossi. "NanoCockpit: Performance-optimized 
 *    Application Framework for AI-based Autonomous Nanorobotics"
 * We kindly ask for a citation if you use in academic work.
 */

#ifndef __CPX_WIFI_H__
#define __CPX_WIFI_H__

#include <esp_wifi.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Fallback SSID of the AI-deck in AP mode, used when cpx_wifi_init() is given none */
#define WIFI_SSID "crazyflie"

/* TCP and UDP local ports */
#define PORT 5000  // upstream default. 2026-11-11..19 used 443 while the VCU firewall blocked 5000;
                   // IT has since opened TCP+UDP 5000-5010 (verified 2026-11-19).

/* Access point channel.
   2026-11-13: channel 11 seemed to fail with the radio connected, but the real cause was the
   Crazyradio dongle sitting next to the PC's Wi-Fi antennas (it jammed channel 1 just as badly).
   2026-11-16: with the dongle moved, channel 1 was crowded by a strong VCU campus AP (ping
   100-300 ms, 13.8 fps), so channel 11 was tried: 9-11 fps, worse, because the radio at
   2480 MHz sits right above it. Back on channel 1: 18.5-19 fps with the radio on or off.
   Builds: ~/aideck_cpx_streamer_port5000_ch1.bin (deployed), ..._port443_ch1.bin, ..._port443_ch11.bin. */
#define WIFI_AP_CHANNEL 1

/* Initialize the WiFi */
void cpx_wifi_init(wifi_mode_t mode, const char *ssid, const char *key);

/* Check if Wi-Fi has been started */
bool wifi_has_started();

/* Wait (and block) until a connection comes in */
void wifi_wait_for_socket_connected();

/* Bind socket for incomming connections */
void wifi_bind_socket();

/* Check if a client is connected */
bool wifi_is_socket_connected();

/* Wait (and block) for a client to disconnect */
void wifi_wait_for_disconnect();

/* Send a packet to the client from buffer of size */
void wifi_send_packet(const uint8_t *buffer, size_t size);

/* Wait (and block) for a received packet */
void wifi_receive_packet(uint8_t **buffer);
void wifi_release_receive(uint8_t *buffer);

#endif /* __CPX_WIFI_H__ */
