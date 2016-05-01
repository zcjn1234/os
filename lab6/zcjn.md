��ϰ1: ʹ�� Round Robin �����㷨������Ҫ���룩

Round Robin�����㷨��˫����������һ����Ա������
��ʾ�ڴ˾������̶����е����ִ��ʱ��Ƭ.
��proc_struct������һ����Ա����time_slice����¼������ʱ��Ƭ�Ρ�
��ÿ��timer��ʱ������ϵͳ��ݼ�ִ�н��̵�time_slice���䵽0ʱ��
��CPU�ø��������̣��˽��̻ص���β������ʱ��ƬΪmax_time_slice��
ȡһ���µĽ���ִ�С�

��ϰ2: ʵ�� Stride Scheduling �����㷨����Ҫ���룩
������default_sched_stride_c����default_sched.c��Ȼ�����Stride�����㷨��ʵ�֡�
�����ʵ���ĵ����ָ�����Stride�����㷨�Ĵ����������������Stride�����㷨��һЩ��ص����ϣ�Ŀǰ�������ĵ����ϱȽ�Ƿȱ����
strid-shed paper location1
strid-shed paper location2
Ҳ��GOOGLE ��Stride Scheduling�� �������������
ִ�У�make grade���������ʾ��Ӧ�ó����ⶼ���ok���������ȷ�����ֻ��priority.c����ȥ����ִ�� make run-priority ����������������.


static int
proc_stride_comp_f(void *a, void *b)
{
     struct proc_struct *p = le2proc(a, lab6_run_pool);
     struct proc_struct *q = le2proc(b, lab6_run_pool);
     int32_t c = p->lab6_stride - q->lab6_stride;
     if (c > 0) return 1;
     else if (c == 0) return 0;
     else return -1;
}


static void
stride_init(struct run_queue *rq) {
     /* LAB6: YOUR CODE */
     list_init(&(rq->run_list));
     rq->lab6_run_pool = NULL;
     rq->proc_num = 0;
}


static void
stride_enqueue(struct run_queue *rq, struct proc_struct *proc) {
     /* LAB6: YOUR CODE */
#if USE_SKEW_HEAP
     rq->lab6_run_pool =
          skew_heap_insert(rq->lab6_run_pool, &(proc->lab6_run_pool), proc_stride_comp_f);
#else
     assert(list_empty(&(proc->run_link)));
     list_add_before(&(rq->run_list), &(proc->run_link));
#endif
     if (proc->time_slice == 0 || proc->time_slice > rq->max_time_slice) {
          proc->time_slice = rq->max_time_slice;
     }
     proc->rq = rq;
     rq->proc_num ++;
}


static void
stride_dequeue(struct run_queue *rq, struct proc_struct *proc) {
     /* LAB6: YOUR CODE */
#if USE_SKEW_HEAP
     rq->lab6_run_pool =
          skew_heap_remove(rq->lab6_run_pool, &(proc->lab6_run_pool), proc_stride_comp_f);
#else
     assert(!list_empty(&(proc->run_link)) && proc->rq == rq);
     list_del_init(&(proc->run_link));
#endif
     rq->proc_num --;
}

static struct proc_struct *
stride_pick_next(struct run_queue *rq) {
     /* LAB6: YOUR CODE */
#if USE_SKEW_HEAP
     if (rq->lab6_run_pool == NULL) return NULL;
     struct proc_struct *p = le2proc(rq->lab6_run_pool, lab6_run_pool);
#else
     list_entry_t *le = list_next(&(rq->run_list));

     if (le == &rq->run_list)
          return NULL;
     
     struct proc_struct *p = le2proc(le, run_link);
     le = list_next(le);
     while (le != &rq->run_list)
     {
          struct proc_struct *q = le2proc(le, run_link);
          if ((int32_t)(p->lab6_stride - q->lab6_stride) > 0)
               p = q;
          le = list_next(le);
     }
#endif
     if (p->lab6_priority == 0)
          p->lab6_stride += BIG_STRIDE;
     else p->lab6_stride += BIG_STRIDE / p->lab6_priority;
     return p;
}
