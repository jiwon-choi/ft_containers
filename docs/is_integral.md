# std::is_integral

```cpp
template <class T> struct is_integral;
```

- T가 정수 유형인지 여부를 식별하는 특성 클래스이다.
- T가 정수 형식인지 여부에 따라 정수형 상수를 true_type, 또는 false_type으로 상속한다.
- 기본 integral 형식 : bool, char, short, int, long, long long (enum은 C++에서 정수형으로 간주하지 않는다.)

## std::integral_constant

```cpp
template <class T, T v>
struct integral_constant {
  static constexpr T value = v;
  typedef T                         value_type;
  typedef integral_constant<T, v>   type;
  constexpr operator T() { return v; }
};
```

- 이 템플릿은 compile time 상수를 type으로 제공하도록 설계되었다.
- 표준 라이브러리의 여러 부분에서(특히 bool 변형에서) 특성 유형의 기본 클래스로 사용된다.

- value_type : 상수 타입, T
- type : integral_constant 자기 자신
- operator value_type : integral_constant의 값을 반환한다.
  true_type의 경우 true, false_type의 경우 false이다.
