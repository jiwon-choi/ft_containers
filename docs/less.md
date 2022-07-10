# std::less

```cpp
template <class T> struct less;
```

- 비교를 위한 함수 객체이다.
- 유형 T에서 operator<를 호출한다. 따라서 첫 번째 인수가 두 번째 인수보다 작은지 여부를 반환한다.
- operator<를 호출하므로 당연히 bool을 반환한다!
