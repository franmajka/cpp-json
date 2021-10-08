#pragma once

template <class Class, typename T>
struct Property {
  using Type = T;

  constexpr Property(const char* aName, T Class::*aMember) : name(aName), member(aMember) {}

  const char* name;
  T Class::*member;
};

template <class Class, typename T>
constexpr auto property(const char* name, T Class::*member) {
  return Property<Class, T>(name, member);
}

