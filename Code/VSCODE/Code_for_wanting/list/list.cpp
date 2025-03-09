#include<iostream>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
//移除链表元素
class Solution_D {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            //【这个判断可以不要（接下来囊括了）】
            if(!head)return head;//为空才进入
        //避免麻烦，直接做一个虚拟头节点
            ListNode* new_H = new ListNode(0,head);
            ListNode* p = new_H;
            while((p->next)){//不为空才进入
                if((p->next)->val==val){
                    ListNode* f = p->next;//直接初始化
                    //f = p->next;
                    p->next = f->next;
                    delete f;
                }
                else{//这里一定是否则       ；如果下一个符合，进上面【指针不需要后移】
                    p = p->next;
                } 
            }
            ListNode* res = new_H->next;
            delete new_H; 
            return head;
        }
};
//  很臭    反转链表
// class Solution_R_LOSER {
//     public:
//         ListNode* reverseList(ListNode* head) {
//             ListNode* Head_v1 = new ListNode(0);
//             ListNode* Head_v2 = new ListNode(0);
//             //ListNode* N_p = Head_v1;
//             Head_v2->next = head;
//             Head_v1->next = Head_v2;
//             ListNode* New_Head = new ListNode(0);
//             ListNode* N_p = New_Head;
//             while(head){
//                 ListNode* p = Head_v1;
//                 while(p->next->next){
//                     p = p->next;
//                 }
//                 //if(!New_Head)New_Head->next = p;
//                 if(!N_p)N_p = p->next;
//                 else{
//                     N_p->next = p->next;
//                 }
//                 //N_p = N_p->next;
//                 if(p->next == head)head=NULL;
//                 p->next = NULL;
//                 p = Head_v1;
//             }
//             return New_Head;
//         }
//     };
void Print(ListNode* l){
    ListNode* p = l;
    for(int i= 0;i<=5;i++){
        
        printf("%d",p->val);p = p->next;
    }
}
//双指针写法    temp记忆cur->next避免丢失
class Solution_R{
    public:
    ListNode* reverseList(ListNode* head){
        ListNode* pre = NULL;
        ListNode* cur = head;
        while(cur){
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }return pre;
    }
};
//          递归写法
class Solution_R_D{
   //递归
    public: ListNode* reverse(ListNode* pre,ListNode* cur){
        if(!cur)return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        reverse(cur,temp);
    }
    ListNode* reverseList(ListNode* head){
        return reverse(NULL,head);
    } 
};
//自己设计链表
class MyLinkedList {
    public:
        struct LinkedNode{
            int val;
            LinkedNode* next;
            LinkedNode(int val = 0):val(val),next(nullptr){}
        };
        MyLinkedList() {
            dummyhead = new LinkedNode();
            size = 0;
        }
        
        int get(int index) {
            if(index<0||index > size-1){
                return -1;
            }
            else{
                LinkedNode* cur = dummyhead->next;
                while(index--){
                    cur = cur->next;
                }
                return cur->val;
            }
        }
        
        void addAtHead(int val) {
            LinkedNode* p = new LinkedNode(val);
            p->next = dummyhead->next;
            dummyhead->next = p;
            size++;
        }
        //尾删法时如果用下标来找，需要考虑空链表的处理
        //所以寻找cur->next == NULL
        void addAtTail(int val) {
            LinkedNode* cur = dummyhead;
            // int size_ = size;
            // while(size_--){
            //     cur=cur->next;
            // }
            while (cur->next!=nullptr)
            {
                cur = cur->next ;
            }
            
            LinkedNode* p = new LinkedNode(val);
            cur->next = p;size++;
        }
        
        void addAtIndex(int index, int val) {
            LinkedNode* cur = dummyhead;
            if(index>size||index<0)return;
            //if(index==size)index--;
            while(index--){
                cur = cur->next;
            }
            LinkedNode* p = new LinkedNode(val);
            p->next = cur->next;
            cur->next = p;
            size++;
        }
        
        void deleteAtIndex(int index) {
            LinkedNode* cur = dummyhead;
            if(index>size||index<0)return;
            while (index--)
            {
                cur = cur->next;
            }
            LinkedNode* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
            size--;
        }
    public:
        LinkedNode* dummyhead;
        int size;
    };
//两两交换
class Solution_exchange {
    public:
        ListNode* swapPairs(ListNode* head) {
            ListNode* dummyhead = new ListNode(0);
            dummyhead->next = head;
            ListNode* cur = dummyhead;
            while(cur->next!=nullptr&&cur->next->next!=nullptr){
                ListNode* p = cur->next;
                cur->next = p->next;
                p->next = p->next->next;
                cur->next->next = p;
                //自己画图理解最好，该删的箭头删掉
                cur = cur->next->next;//更新cur
            }
            return dummyhead->next;
        }
    };
//删除倒数第n个结点【进阶：一趟循环】

class Solution_simple {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            ListNode* dummyhead = new ListNode(0);
            dummyhead->next =head;
            int size = 0;
            ListNode* cur = head;
            while(cur){
                cur = cur->next;size++;
            }
            if(size==0||n>size){}
            else{cur = dummyhead;
                int index = size-n;
                while(index--){
                    cur = cur->next;
                }
                ListNode* p =cur->next;
                cur->next = cur->next->next;
                delete p;
            }
            return dummyhead->next;
        }
    };
//进阶：双指针的方法，快慢指针位移 相差 n 
    class Solution_improve{
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            ListNode* dummyhead = new ListNode(0);
            dummyhead->next = head;
            ListNode* slow = dummyhead;
            ListNode* fast = dummyhead;
            for(int i=0;i<n;i++)fast = fast->next;
            while(fast->next){
                fast = fast->next;
                slow = slow->next;
            }
            ListNode* p = slow->next;
            slow->next = slow->next->next;
            delete p;
            return dummyhead->next;
        }
};
//  相交结点    【两节点的地址相同】
#include<bits/stdc++.h>
//#include<algorithm>
class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            ListNode* curA = headA;
            ListNode* curB = headB;
            int lenA = 0,lenB = 0;
            while(curA){
                curA = curA->next;lenA++;
            }
            while(curB){
                curB = curB->next;lenB++;
            }curA =headA;curB = headB;
            //交换函数swap（）来自 algorithm
            if(lenB>lenA){
                std::swap(curA,curB);
                std::swap(lenA,lenB);
                // swab((char*)&lenA,(char*)&lenB,sizeof(int));
                // swab((char*)&curA,(char*)&curB,sizeof(ListNode*));
            }
            int gap = lenA-lenB;
            // ListNode* dummyheadA = new ListNode(0);
            // ListNode* dummyheadB = new ListNode(0);
            // dummyheadA->next = headA;dummyheadB = headB;
            // curA = dummyheadA;curB = dummyheadB;
            while(gap--){
                curA = curA->next;
            }
            while(curA){
                if(curA == curB)return curA;
                curA = curA->next;
                curB = curB->next;
            }return nullptr;
        }
    };
//环形链表2 【找到环的开始处】  【这道题的数学推导是关键】
class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode* slow = head;
            ListNode* fast = head;
            while(fast&&fast->next){
                fast = fast->next->next;
                slow = slow->next;
                if(fast==slow){
                    ListNode* index1 = head;
                    ListNode* index2 = slow;
                    while(index1!=index2){
                        index1=index1->next;
                        index2=index2->next;
                    }
                    return index1;
                }
            }return nullptr;
        }
    };
//环形链表【判断存在环】
class Solution {
    public:
        bool hasCycle(ListNode *head) {
            if (!head || !head->next)
                return false;//多写这么一个if语句，运行时间会快很多

            ListNode* slow = head;      
            ListNode* fast = head;
            while(fast&&fast->next){
                fast = fast->next->next;
                slow = slow->next;
                if(slow==fast)return true;
            }return false;
        }
    };
//快乐数    【方法一：集合，新元素是否成功插入集合中，若失败则进入无限循环D:\VS\Code\VSCODE\Code_for_wanting\list\环形链表找入口.png】
using namespace std;
//方法一：集合
class Solution {
    public:
        int bitSquareSum(int num){
            int sum = 0;
            while(num){
                sum+=(num%10)*(num%10);
                num/=10;
            }return sum;
        }
        bool isHappy(int n) {
            int temp = n;
            set<int> seen;
            seen.insert(n);
            while(n!=1){
                n = bitSquareSum(n);
                if(seen.insert(n).second==false)return false;
            }return true;
        }
    };
//方法二：快慢指针，【类似求环形链表】 出循环slow==fast，在判断slow==1
    class Solution {
        public:
            int bitSquareSum(int num){
                int sum = 0;
                while(num){
                    sum+=(num%10)*(num%10);
                    num/=10;
                }return sum;
            }
            bool isHappy(int n) {
                int slow = n,fast = n;
                do{
                    slow = bitSquareSum(slow);
                    fast = bitSquareSum(fast);
                    fast = bitSquareSum(fast);
                }while(slow!=fast);
                return (slow==1);
            }
        
    };
//方法三：数学推导 当循环中出现 4 37 58 89 145 42 20 4  【死循环，有且仅有着一种情况】
class Solution {
    public:
        int bitSquareSum(int num){
            int sum = 0;
            while(num){
                sum+=(num%10)*(num%10);
                num/=10;
            }return sum;
        }
        bool isHappy(int n) {
            while(n!=1){
                if(n==4||n==37||n==58||n==89||n==145||n==42||n==20){
                    return false;
                }
                n = bitSquareSum(n);
            }return true;
        }
};
int main(){
    ListNode* head = new ListNode(0);
    ListNode* h_p = head;
    for(int i=1;i<=5;i++){
        ListNode* p = new ListNode(i);
        h_p->next = p;
        h_p = h_p->next;
    }

    Solution_R_D s_r;
    ListNode* new_ = s_r.reverseList(head);

    ListNode* p = new_;
    // Print(head);
    // ListNode* p = head;
    for(int i= 0;i<=5;i++){
        
        printf("%d",p->val);
        p = p->next;
    }
    return 0;
}