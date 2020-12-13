



class Pin {
  protected:
    uint8_t const pin;

    void mode (int const mode) const {
      pinMode(pin, mode);
    }

    int reverseLogic(int const level) const {
      return (level == LOW) ? HIGH : LOW;
    }

  public:
    Pin(uint8_t const pin_): pin(pin_) {}

    int read() const {
      return digitalRead(pin);
    }
};

class PinIn: public Pin {
  public:
    PinIn(uint8_t const pin_): Pin(pin_) {
      mode(INPUT);
    }
};

class PinInReverseLogic: public PinIn {
  public:
    PinInReverseLogic(uint8_t const pin_): PinIn(pin_) {}

    int read() const {
      return reverseLogic(Pin::read());
    }
};

class PinOut : public Pin {
  protected:
    void write(int const level) {
      digitalWrite(pin, level);
    }

  public:
    PinOut(uint8_t const pin_): Pin(pin_) {
      mode(OUTPUT);
    }

    void high() const {
      write(HIGH);
    }

    void low() const {
      write(LOW);
    }

    void toggle() const {
      out(reverseLogic(read()));
    }

    void out(bool const bit) const {
      (bit == true) ? high() : low();
    }

    void out(int const level) const {
      out(level != LOW);
    }
};

class PinOutReverseLogic : public PinOut {
  protected:
    void write (int const level) {
      PinOut::write(reverseLogic(level));
    }

  public:
    PinOutReverseLogic(uint8_t const pin_): PinOut(pin_) {
    }
};

PinOut led(LED_BUILTIN);



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  led.toggle();
  delay(50);
}
