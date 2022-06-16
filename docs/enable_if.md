# std::enable_if

```cpp
template <bool Cond, class T = void> struct enable_if {};
template <class T> struct enable_if<true, T> { typedef T type; };
```

- Enable type if condition is met
- Cond가 true인 경우 유형 T는 enable_if::type 유형으로 활성화된다.
  그렇지 않은 경우에는 enable_if::type이 정의되지 않는다.
- enable_if는 특정 조건이 충족되지 않을 때 compile time에 특징을 숨기는 데 유용하다.
  enable_if::type 멤버가 정의되지 않고 이를 사용한 컴파일 시도가 실패해야 하기 때문이다.

## SFINAE
- Substitution Failure Is Not An Error
- https://modoocode.com/255
