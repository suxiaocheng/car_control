#include "car_control.h"

pthread_mutex_t global_lock;
int threads_running = 0;
pthread_attr_t thread_attr;
pthread_t httpd_thread_id;

static void *httpd_loop(void *arg)
{
	arg = arg;
	pthread_mutex_lock(&global_lock);
	threads_running--;
	pthread_mutex_unlock(&global_lock);
	DEBUG("httpd_loop exit\n");
}

int main(int argc, char **argv)
{
	init_log_file(LOG_FILE_NAME);
	DEBUG("main start\n");
	pthread_mutex_lock(&global_lock);
	threads_running++;
	pthread_mutex_unlock(&global_lock);

	pthread_attr_init(&thread_attr);
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&httpd_thread_id, &thread_attr, &httpd_loop, NULL)) {
		/* thread create failed, undo running state */
		pthread_mutex_lock(&global_lock);
		threads_running--;
		pthread_mutex_unlock(&global_lock);
		ERR("pthread create fail\n");
	}
	pthread_attr_destroy(&thread_attr);

	while (threads_running > 0) {
		sleep(1);
	}
	DEBUG("main exit\n");
	close_log_file();

	return 0;
}
