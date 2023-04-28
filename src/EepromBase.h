/*
 * Copyright (C) 2023 epsilonrt <epsilonrt@gmail.com>
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include <EEPROM.h>
#include <assert.h>
#pragma once

// Meyer's singleton
template<class Dummy>
struct EepromBaseStatic {
    static uint16_t counter;
};

template<class Dummy>
uint16_t EepromBaseStatic<Dummy>::counter = 0;

/**
 * @brief EEPROM memory storage management class
 */
class EepromBase : public EepromBaseStatic<void> {};
