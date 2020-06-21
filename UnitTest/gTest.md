# Primary
## Basic Assertions
|  触发中断   | 不触发中断  |
|  ----  | ----  |
| `ASSERT_TRUE(condition)`  | `EXPECT_TRUE(condition)` |
| `ASSERT_FALSE(condition)`  | `EXPECT_FALSE(condition)` |

## 条件宏：
- `ASSERT_EQ`
- `ASSERT_NE (!=)`
- `ASSERT_LT (<)`
- `ASSERT_LE (<=)`
- `ASSERT_GT (>)`
- `ASSERT_GE (>=)`

## 字符串比较
`ASSERT_STREQ(str1,str2)` 用于比较C类型的字符串，如果比较`srting`，用`ASSERT_EQ`

## 简单例子
```C++ 
TEST (TestSuiteName, TestName){
    ... ...
}
```

### Test Fixtures
避免写太多类似重复的`Case`
```C++ 
TEST_F (TestFixtureName, TestName){
    ... ...
    //全局共享的变量可以用静态变量
    static shared_pointer*;
    
    //在类外部声明，在这个函数中初始化
    static void SetUpTestCase() {
      shared_pointer = new T();
    }

    //在这里清除，这个与官方文档有出入
    static void TearDownTestCase() {
      delete shared_pointer;
      shared_pointer = nullptr;
    }
}
```
例子，需要测试的类：
```C++
template <typename E>  // E is the element type.
class Queue {
 public:
  Queue();
  void Enqueue(const E& element);
  E* Dequeue();  // Returns NULL if the queue is empty.
  size_t size() const;
  ...
};
```
test fixture类
```C++
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {} 
  // 用于清理所用的内存
  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};
```








