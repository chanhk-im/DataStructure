DataStructure
=============
HGU ECE20010-04 데이타구조 수업 자습

## 1. 데이터 구조 수업 관련 사이트
1. https://piazza.com/class/k7aho8gvmbc22e
1. https://github.com/hongshin/DataStructure/wiki

## 2. 리스트(List)

### 1. 배열 리스트(Array List)

* `ArrayList *ListInit()` ArrayList 하나를 메모리에 동적 할당하고 그 메모리 주소를 반환
* `void LInsert(ArrayList *plist, int data)` ArrayList 맨 뒤에 data값의 원소 추가
* `int LDelete(ArrayList *plist, int pos, int *e)` pos번째 원소 삭제 후 그 원소의 값을 e에 저장
* `int LSearch(ArrayList *plist, int pos, int *e)` pos번째 원소의 값을 e에 저장
* `int ListLength(ArrayList *plist)` ArrayList의 길이 반환

### 2. 연결 리스트(Linked List)