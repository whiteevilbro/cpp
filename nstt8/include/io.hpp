#ifndef IO_H_
#define IO_H_

struct IO {
  enum iostate {
    goodbit  = 0,
    eofbit   = 0b01,
    closebit = 0b10,
  };

  void setstate(iostate state) {
    this->state = static_cast<iostate>(state | this->state);
  }

  void clear(iostate state = iostate::goodbit) {
    this->state = state;
  }

  iostate rdstate() const {
    return state;
  }

  bool eof() const {
    return static_cast<bool>(state & iostate::eofbit);
  }

  bool good() const {
    return !static_cast<bool>(state);
  }

  bool is_open() const {
    return static_cast<bool>(state & iostate::closebit);
  }

  void virtual close() {
    setstate(closebit);
  }

  virtual ~IO() {
    close();
  }

private:
  iostate state;
};

#endif
