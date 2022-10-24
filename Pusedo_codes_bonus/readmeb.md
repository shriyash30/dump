
BONUS PROBELM 2: THREAD 2 RECEIVE THE MESSAGE TO PRINT AND THE TIME DELAY AFTER WHICH TO PRINT THE MESSAGE FROM THREAD1 IN THE SAME MESSAGE

step1 :mystring = "thread 2:"+setdelayt;  // send the string in this format

step2 :k_fifo_put(mystring);

step3 :char msg;char receiveddelaystring; int receiveddelay,j;

step4 :Inside thread 2
 step4.1 : rxstring=k_fifo_get();
 step4.2 :for(i=0;i<sizeof(rxstring);i++)
 {
 if(mystring[i]==":"
 {
 receiveddelaystring[j]=mystring[i];        //extract substring
 j++
 }
 else
 {
 msg[k]=mystring[i];                  
 k++
 }
 receiveddelay=int(receivedelaystring);
 step 4.3: print(msg);
 step 4.4: sleep(receiveddelay);

step 5:END



