#ifndef FastPin_h
#define FastPin_h

#include <Arduino.h>

class FastWritePin {
   public:
    /// @brief Constructs a new pin object for writing at high speeds.
    ///
    /// @param pin: The pin number.
    FastWritePin(byte pin);

    /// @brief Initializes the pin, sets the mode and disables PWM timers.
    ///
    /// @attention This function must be called before `write()`.
    ///
    /// @param initialVal: The initial value of the pin. Default is LOW.
    void begin(bool initialVal = LOW);

    /// @brief Writes a digital value to the pin at high-speed.
    ///
    /// @attention `begin()` must be called before this function.
    ///
    /// @param val: The value to write.
    void write(bool val);

   private:
    /// The pin number.
    byte _pin;

    /// The bit mask of the pin.
    byte _bitMask;

    /// The output register of the  pin.
    volatile byte *_outputRegister = NULL;
};

class FastReadPin {
   public:
    /// @brief Constructs a new pin object for reading at high speeds.
    ///
    /// @param pin: The pin number.
    FastReadPin(byte pin);

    /// @brief Initializes the pin, sets the mode and disables PWM timers.
    ///
    /// @attention This function must be called before `read()`.
    ///
    /// @param pullup: Enable or disable the pullup resistor. Default is false.
    void begin(bool pullup = false);

    /// @brief Returns the digital value of the pin at high-speed.
    ///
    /// @attention `begin()` must be called before this function.
    bool read();

   private:
    /// The pin number.
    byte _pin;

    /// The bit mask of the step pin.
    byte _bitMask;

    /// The input register of the step pin.
    volatile byte *_inputRegister = NULL;
};

#endif