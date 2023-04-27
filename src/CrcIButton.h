/*
 * Copyright (C) 2023 epsilonrt <epsilonrt@gmail.com>
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include <stdint.h>
#include <stddef.h>
#pragma once


// Classe CrcIButton
// Calcul du CRC IButton
template<class T>
class CrcIButton {
  public:
    // Valeur initiale du CRC
    const static uint8_t InitValue = 0x5A;
    // Constructeur
    CrcIButton () : m_ucCrc (InitValue) {}
    // Réinitialisation du CRC
    void reset () {
      m_ucCrc = InitValue;
    }
    // Valeur du CRC
    uint8_t value () const {
      return m_ucCrc;
    }
    // Mise à jour du CRC
    void update (const T &value) {
      const uint8_t *buf = reinterpret_cast<const uint8_t *> (&value);
      size_t len = sizeof (T);
      while (len--) {
        m_ucCrc = CrcIButtonUpdate (m_ucCrc, *buf++);
      }
    }
  private:
    uint8_t m_ucCrc; // Valeur du CRC
    // Mise à jour du CRC octet par octet
    static inline uint8_t CrcIButtonUpdate (uint8_t crc, uint8_t data) {
      unsigned int i;

      crc = crc ^ data;
      for (i = 0; i < 8; i++) {
        if (crc & 0x01) {
          crc = (crc >> 1) ^ 0x8C;
        }
        else {
          crc >>= 1;
        }
      }
      return crc;
    }
};
