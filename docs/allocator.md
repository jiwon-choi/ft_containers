# std::allocator

```cpp
template <class T> class allocator;
```

- 기본 allocator
- Allocator는 표준 라이브러리의 일부, 특히 STL 컨테이너에서 사용할 메모리 모델을 정의하는 클래스이다.
- std::allocator는 모든 표준 컨테이너가 마지막 템플릿 매개변수가 지정되지 않은 경우 사용할 할당자이고, 표준 라이브러리에서 유일하게 사전 정의된 할당자이다.
- 다른 할당자를 정의할 수 있다. 이 기본 할당자와 동일한 멤버를 가지고 최소 요구사항을 만족하는 모든 클래스는 표준 컨테이너와 함께 할당자로 사용이 가능하다.
- T : 할당된 요소의 유형, value_type으로 별칭 지정됨

## member functions

- (constructor)
- (destructor)
- address : 매개변수로 받아온 레퍼런스 x의 주소값을 반환한다.
  ```cpp
  pointer address(reference x) const;
  const_pointer address(const_reference x) const;
  ```
- allocate : 메모리 블록을 할당한다.
  ```cpp
  pointer allocate(size_type n, allocator<void>::const_pointer hint=0);
  ```
  value_type 유형이 n개 포함될 수 있을 만큼 충분히 큰 메모리를 할당하고, 첫 번째 요소를 반환한다.
  표준 allocator는 new 연산자를 한 번 이상 사용하여 메모리를 할당하고, 필요한 만큼 할당할 수 없는 경우 bad_alloc을 throw한다.  
  hint에 가까운 메모리 위치에 대한 포인터를 넣어주면 가능한 한 가깝게 새 메모리 블록을 할당하려고 시도한다.
- deallocate : 할당된 블록을 해제한다.
  ```cpp
  void deallocate(pointer p, size_type n);
  ```
  이전에 allocate으로 할당되었지만 아직 해제되지 않은 메모리를 해제한다.
  배열 내부의 요소들은 deallocate에 의해 해제되지 않는다.
  표준 allocator는 delete 연산자를 사용하여 할당을 해제한다.
- max_size : 할당 가능한 최대 크기를 반환한다.
  ```cpp
  size_type max_size() const throw();
  ```
  allocate에 의해 _잠재적으로_ 할당될 수 있는 value_type의 최대 요소 수를 반환한다.
  이 반환값을 사용하여 allocate를 호출하더라도 할당이 항상 가능함을 보장하지는 않는다.
- construct : 매개변수 p가 가리키는 위치에 객체를 생성한다.
  ```cpp
  void construct(pointer p, const_reference val);
  ```
  construct는 메모리 할당에 관여하지 않는다. 이미 p 위치가 사용가능해야 한다.
  val의 복사본으로 초기화하기 위해 내부적으로 아래 코드처럼 복사 생성자를 사용한다.
  ```cpp
  new ((void *)p) value_type(val);
  ```
- destroy : 매개변수 p가 가리키는 객체를 삭제한다.
  ```cpp
  void destroy(pointer p);
  ```
  destroy도 construct와 마찬가지로 메모리 해제에 관여하지 않는다.
  p가 가리키는 객체를 삭제하기 위해 내부적으로 아래 코드처럼 value_type의 소멸자를 사용한다.
  ```cpp
  p->~value_type();
  ```

## Template specializations
- rebind
  ```cpp
  template <> class allocator<void> {
    public:
    template <class U> struct rebind { typedef allocator<U> other; };
  }
  ```
  http://egloos.zum.com/sweeper/v/2966785  
  중첩 구조체 템플릿  
  allocator에 넘긴 T 타입 이외의 다른 타입에 대한 allocate가 필요한 경우 사용한다. (다른 타입 == 해당 컨테이너에서 요구되는 진정한 할당 타입)
  