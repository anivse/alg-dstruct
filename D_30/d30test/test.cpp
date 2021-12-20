#include "pch.h"
#include "d30.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(IsInArrTest, if_this_value_is_in_arr_return_1) {
	int* arr = (int*)malloc(sizeof(int) * 3);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	int n = IsInArr(arr, 3, 1);
	EXPECT_TRUE(n == 1);
}

TEST(IsInArrTest, if_this_value_is_not_in_arr_return_0) {
	int* arr = (int*)malloc(sizeof(int) * 3);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	int n = IsInArr(arr, 3, 4);
	EXPECT_TRUE(n == 0);
}

TEST(IsInQueueTest, if_this_value_is_in_queue_return_1) {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = (list_t*)malloc(sizeof(list_t));
	queue->head->field = 1;
	queue->head->next = NULL;
	queue->tail = queue->head;
	int n = IsInQueue(queue, 1);
	EXPECT_TRUE(n == 1);
}

TEST(IsInQueueTest, if_this_value_is_not_in_queue_return_0) {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = (list_t*)malloc(sizeof(list_t));
	queue->head->field = 0;
	queue->head->next = NULL;
	queue->tail = queue->head;
	int n = IsInQueue(queue, 1);
	EXPECT_TRUE(n == 0);
}

TEST(AddInQueueTest, if_add_value_in_queue_tail_field_is_value) {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = (list_t*)malloc(sizeof(list_t));
	queue->head->field = 0;
	queue->head->next = NULL;
	queue->tail = queue->head;
	AddInQueue(queue, 1);
	EXPECT_EQ(queue->tail->field, 1);
}
TEST(DeleteOutQueueTest, if_delete_out_queue_delete_value_out_head) {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = (list_t*)malloc(sizeof(list_t));
	queue->head->field = 0;
	queue->head->next = NULL;
	queue->tail = queue->head;
	int field = 1;
	queue->tail->next = (list_t*)malloc(sizeof(list_t));
	queue->tail = queue->tail->next;
	queue->tail->field = field;
	queue->tail->next = NULL;
	DeleteOutQueue(queue);
	EXPECT_EQ(queue->head->field, 1);
}

TEST(FoundNextTaskTest, if_one_of_pairs_is_value_return_other_value) {
	pairs_t* pairs = (pairs_t*)malloc(sizeof(pairs_t) * 2);
	pairs[0].one = 1;
	pairs[0].two = 1;
	pairs[1].one = 2;
	pairs[1].two = 3;
	int task = FoundNextTask(pairs, 3, 2);
	EXPECT_EQ(task, 3);
}

TEST(BuildSequenceTest, return_a_sequence_based_on_pairs_of_a_set) {
	int numberT = 3;
	int numberPairs = 2;
	pairs_t* pairs = (pairs_t*)malloc(sizeof(pairs_t) * 3);
	pairs[0].one = 1;
	pairs[0].two = 3;
	pairs[1].one = 3;
	pairs[1].two = 2;
	int* seq = BuildSequence(numberT, pairs, numberPairs);
	EXPECT_EQ(seq[0], 1);
	EXPECT_EQ(seq[1], 3);
	EXPECT_EQ(seq[2], 2);
}