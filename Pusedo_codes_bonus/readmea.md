BONUS PROBLEM 1: USAGE OF THREAD LOCAL VARIABLES FOR MAINTAINING THE THREAD STATES


ALTERNATIVE 1:Without local variable

const char *k_thread_state_str(k_tid_t thread_id, char *buf, size_t buf_size)
- it returns a thread state. Use this to get the state of current thread.







ALTERNATIVE 2: With local variable

step1 : set CONFIG_THREAD_LOCAL_STORAGE CONFIG_ERRNO_IN_TLS CONFIG_ERRNO =1  //enables local storage

step2 : static __thread char thrState[50]; //local thread variable 

step3 : thrState="created" // this statement goes inside thread creation built in function.

step4 : thrState="ready" // this statement will also go inside a built in function to check the status  of readyqueue

step5 : void firstthread(void)
{
    
    thrState="running";
	while (1)
	{  

		char data[50] = "thread 2";
		printk("thread 1 %s\n"); 
        thrState="waiting";
		k_msleep(k * SLEEP_TIME_MS); // puts current thread in sleep for k seconds.
        thrState="running";
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
step6 : END



Note similarly we can write thrState for Thread2





IMP points:
1. k_sleep puts the thread in suspended/ waiting state ( so thread 1 is waiting,then thread 2 is getting
2. k_thread_start - transition of a thread to ready state.
3. struct k_thread can be used to get thread state.
4. k_sleep puts the thread in waiting state so thread 1 is waiting 
5. k_thread_start - transition of a thread to ready state.
6. reference - just look how zephyr itself maintains states of these variables by going thr built in 7. functions.
