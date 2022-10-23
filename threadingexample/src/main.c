
#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/printk.h>
#include <string.h>

#define SLEEP_TIME_MS 1000  // delay of 1 second
#define STACKSIZE 1024 /* size of stack area used by each thread */
#define PRIORITY 7 // scheduling priority used by each thread

struct k_fifo my_fifo;	// fifo is defined
K_FIFO_DEFINE(my_fifo); // fifo init empty fifo (other fifo def didnt work.)

int k = 1; // counter

struct data_item_t
{
	void *fifo_reserved; // 1st word reserved for use by FIFO

	int setdelayt;
	char mystring[50];
};

struct data_item_t tx_data;

void firstthread(void)
{
	while (1)
	{
		char data[50] = "thread 2";
		printk("thread 1 %s\n"); 

		k_msleep(k * SLEEP_TIME_MS); // puts current thread in sleep for k seconds.

		k++;
		if (k == 10)
		{
			k = 1;
		}
		
		strcpy(tx_data.mystring, data);
		tx_data.setdelayt = 1000;

		k_fifo_put(&my_fifo, &tx_data); // send data.
	}
}

void secondthread(void)
{
	while (1)
	{
		struct data_item_t *rx_data;

		rx_data = k_fifo_get(&my_fifo, K_FOREVER); 
		int receiveddelay = rx_data->setdelayt;
		printk(rx_data->mystring);
		printk("\n");
		k_msleep(receiveddelay);
	}
}

K_THREAD_DEFINE(firstthread_id, STACKSIZE, firstthread, NULL, NULL, NULL,
				PRIORITY, 0, 0);
K_THREAD_DEFINE(secondthread_id, STACKSIZE, secondthread, NULL, NULL, NULL,
				PRIORITY, 0, 0);





