/*
 * Copyright (C) 2023 epsilonrt <epsilonrt@gmail.com>
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include <stdint.h>
#include <stddef.h>
#pragma once

/**
 * @brief iButton CRC template class
 * 
 * @tparam T Type of data to calculate CRC
 */
template<class T>
class CrcIButton {
  public:
    /**
     * @brief Initial value of CRC
     */
    const static uint8_t InitValue = 0x5A;

    /**
     * @brief Construct a new Crc I Button object
     */
    CrcIButton () : m_ucCrc (InitValue) {}

    /**
     * @brief Reset CRC value
     */
    void reset () {
      m_ucCrc = InitValue;
    }

    /**
     * @brief Get the value of CRC
     * @return uint8_t 
     */
    uint8_t value () const {
      return m_ucCrc;
    }

    /**
     * @brief Update CRC with a T value
     * 
     * @param value Value to update CRC
     */
    void update (const T &value) {
      const uint8_t *buf = reinterpret_cast<const uint8_t *> (&value);
      size_t len = sizeof (T);
      while (len--) {
        m_ucCrc = CrcIButtonUpdate (m_ucCrc, *buf++);
      }
    }
  private:
    uint8_t m_ucCrc; ///< CRC value
    /**
     * @brief Update CRC with a byte
     * 
     * @param crc  Current CRC value
     * @param data  Byte to update CRC
     * @return Updated CRC value
     */
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
