// singleton<type>::instance() is a singleton instance of a given type.

#ifndef FELICITY_SINGLETON_H
#define FELICITY_SINGLETON_H

namespace felicity {

template<typename T> struct singleton {
  static T& instance() {
    static T object;
    return object;
  }
};

}  // namespace felicity

#endif
