/*
   Copyright (C) 2023 epsilonrt <epsilonrt@gmail.com>
   SPDX-License-Identifier: LGPL-2.1-or-later
*/
#include <EEPROM.h>
#include <assert.h>
#include "CrcIButton.h"
#include "EepromBase.h"
#pragma once

/**
   @brief CRC-controlled EEPROM memory storage template class

   @tparam T data type
*/
template <class T>
class EepromSecureData {

  public:
    /**
       @brief Construct a new Eeprom Secure Data object

       EEPROM memory is allocated automatically, EepromBase::counter is updated with the size of the object
    */
    EepromSecureData () : m_eem (EepromBase::counter) {
      EepromBase::counter += size();
      // assert (EepromBase::counter < EEPROM.length());
    }

    /**
       @brief Construct a new Eeprom Secure Data object with initial data

       @param data  initial data
    */
    EepromSecureData (const T &data) : EepromSecureData() {
      m_data = data;
    }

    /**
       @brief Destroy the Eeprom Secure Data object

       EEPROM memory is saved automatically
    */
    ~EepromSecureData() {
      save();
    }

    /**
       @brief Save data to EEPROM memory with CRC

       @return true
    */
    bool save() {

      updateCrc();
      EEPROM.put (m_eem, m_data);
      EEPROM.write (m_eem + sizeof (T), m_crc.value ());
      #if defined(ESP32) || defined(ESP8266)
      return EEPROM.commit();
      #else
      return true;
      #endif
    }

    /**
       @brief Load data from EEPROM memory with CRC check

       @param defaultData  default data if CRC check failed
       @return true if CRC check passed, data restored from EEPROM memory
       @return false if CRC check failed, data restored from defaultData
    */
    bool load (const T &defaultData = T()) {

      EEPROM.get (m_eem, m_data);
      uint8_t crc = EEPROM.read (m_eem + sizeof (T));
      updateCrc();

      if (m_crc.value () != crc) {
        m_data = defaultData;
        updateCrc();
        save();
        return false;
      }
      return true;
    }

    /**
       @brief Get the size of the object with CRC
    */
    inline uint16_t size() const {
      return sizeof (T) + sizeof (m_crc);
    }

    /**
       @brief Get the data object
    */
    T &data() {
      return m_data;
    }

    /**
       @brief Get the data object as const
    */
    const T &data() const {
      return m_data;
    }

    /**
       @brief Overloaded cast operator to T &

       @return the data object
    */
    operator T &() {
      return m_data;
    }

    /**
       @brief Overloaded cast operator to const T &

       @return the data object
    */
    operator const T &() const {
      return m_data;
    }

    /**
       @brief Overloaded cast operator to T *

       @return pointer to the data object
    */
    T *operator&() {
      return & m_data;
    }

    /**
       @brief Overloaded cast operator to const T

       @return pointer to the data object
    */
    const T *operator&() const {
      return & m_data;
    }

    /**
       @brief Overloaded assignment operator from T
    */
    T &operator= (const T &t) {
      m_data = t;
      updateCrc();
      return m_data;
    }

    /**
       @brief Overloaded assignment operator from EepromSecureData
    */
    EepromSecureData &operator = (const EepromSecureData &rhs) {
      m_data = rhs.m_data;
      return *this;
    }

    /**
       @brief Overloaded equality operator
    */
    bool  operator == (const EepromSecureData &rhs) const {
      return m_data == rhs.m_data;
    }

    /**
       @brief Overloaded not-equality operator
    */
    bool  operator != (const EepromSecureData &rhs) const {
      return ! (*this == rhs);
    }

  protected:
    // update CRC
    void updateCrc () {
      m_crc.reset ();
      m_crc.update (m_data);
    }

  protected:
    uint16_t m_eem; // EEPROM memory address of the object
    T m_data; // data object itself (RAM)
    CrcIButton <T> m_crc; // CRC object
};
