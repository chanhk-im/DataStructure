DataStructure
=============
HGU ECE20010-04 데이타구조 수업 자습

## 1. 데이터 구조 수업 관련 사이트
1. https://piazza.com/class/k7aho8gvmbc22e
2. https://github.com/hongshin/DataStructure

## 2. 리스트(List)

### 1. 배열 리스트(Array List)

* `ArrayList *ListInit()` ArrayList 하나를 메모리에 동적 할당하고 그 메모리 주소를 반환
* `void LInsert(ArrayList *plist, int data)` ArrayList 맨 뒤에 data값의 원소 추가
* `int LDelete(ArrayList *plist, int pos, int *e)` pos번째 원소 삭제 후 그 원소의 값을 e에 저장
* `int LSearch(ArrayList *plist, int pos, int *e)` pos번째 원소의 값을 e에 저장
* `int ListLength(ArrayList *plist)` ArrayList의 길이 반환

### 2. 연결 리스트(Linked List)
1. Ver.1
   * `LinkedList ListAlloc()` NULL pointer 리턴함
   * `void ListPush(LinkedList *l, int e)` 새로운 Node를 동적 할당후 기존의 Linked List 맨 앞에 붙여 줌
   * `int ListRetrieve(LinkedList l, int pos, int *e)` pos번째의 Node의 element를 e에 저장함
   * `int ListLength(LinkedList l)` l의 길이 반환
   * `int ListPop(LinkedList *l, int *e)` 맨 앞의 Node 삭제
   * `int ListRemove(LinkedList l, int e)` e를 element로 가지는 Node 삭제
  
2. Ver.3, Ver.4, Doubly
   * `linkedlist_t *linkedlist_alloc(int unit)` linkedlist를 동적할당하고 그것을 리턴
   * `void linkedlist_free(linkedlist_t *l)` linkedlist 삭제
   * `int linkedlist_length(linkedlist_t *l)` linkedlist의 길이 반환
   * `void linkedlist_insert_first(linkedlist_t *l, void *e)` linkedlist의 맨 앞에 원소 추가
   * `void linkedlist_insert_last(linkedlist_t *l, void *e)` linkedlist의 맨 뒤에 원소 추가
   * `int linkedlist_remove(linkedlist_t *l, node_t *n)` linkedlist에서 n 삭제
   * `int linkedlist_remove_first(linkedlist_t *l, void *e)` linkedlist의 맨 앞 원소 삭제
   * `int linkedlist_remove_last(linkedlist_t *l, void *e)` linkedlist의 맨 뒤 원소 삭제
   * `int linkedlist_get(linkedlist_t *l, int pos, void *e)` linkedlist에서 pos번째 원소 가져옴
