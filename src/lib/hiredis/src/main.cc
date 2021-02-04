#include <stdio.h>
#include <time.h>
#include <memory>
#include <sstream>
#include <tmbase/log.h>
#include "hiredis.h"
#include "base/base.h"
#include "base/time.h"
//#include "cross_day_timer.h"


constexpr int  kUpdateHour = 8;

int log_init_ex(const char *dir, log_lvl_t lvl, uint32_t size, int maxfiles, const char *pre_name, uint32_t logtime)
{
	int ret;

	if(logtime == 0)
	{
		ret = log_init(dir, lvl, size, maxfiles, pre_name);
	}else{
		ret = log_init_t(dir, lvl, pre_name, logtime);
	}

	return ret;
}
void Init()
{
	INIT_DEFAULT_LOGGER_SYSTEM("./log",
	                           "0",
	                           "mytest",
	                           9292,
	                           "");
	int log_time_interval = 3600;

	if(log_time_interval < 0 || log_time_interval > 86400)
	{
		log_time_interval = 900;
	}

	SET_MAX_ONE_SIZE(100);
	SET_TIME_SLICE_SECS(log_time_interval);
	SET_LOG_LEVEL(tlog_lvl_debug);
	// init log files
	log_init_ex("./log",
	            log_lvl_trace,
	            1 << 3,
	            100,
	            "",
	            0);
}
#if 0
void test_time()
{
	base::Time now;
	
	online::CrossDayTimer cross_day;
	cross_day.set_update_hour(18);
	cross_day.proc_events(now);

	DEBUG_LOG("17:57:0");
	now.SetNowTime(17, 57, 0);
	cross_day.proc_events(now);

	DEBUG_LOG("17:58:0");
	now.SetNowTime(17, 58, 0);
	cross_day.proc_events(now);

	DEBUG_LOG("17:58:1");
	now.SetNowTime(17, 58, 1);
	cross_day.proc_events(now);

	DEBUG_LOG("18:0:0");
	now.SetNowTime(18, 0, 0);
	cross_day.proc_events(now);

	DEBUG_LOG("19:0:0");
	now.SetNowTime(19, 0, 0);
	cross_day.proc_events(now);

	time_t t = time(NULL);
	struct tm lt = {0};

	localtime_r(&t, &lt);
	printf("tm_gmtoff:%ld, tm_zone:%s\n", lt.tm_gmtoff, lt.tm_zone);

	base::Time tt;
	time_t last_daily_time = tt.GetLastDailyUpdateTime(0);
	std::string ss = tt.GetTimeFormatString("l", last_daily_time);
	printf("ss:%s\n", ss.c_str());

	time_t next_daily_time = tt.GetNextDailyUpdateTime(0);
	ss = tt.GetTimeFormatString("l", next_daily_time);
	printf("next:%s\n", ss.c_str());

	tt.s_timeadd(3600 * 24);
	ss = tt.GetTimeFormatString("l");
	printf("tt:%s\n", ss.c_str());

	base::Time special;
	bool is_cross = tt.IsCrossDay(8, (time_t)special.seconds());
	printf("is cross:%s\n", is_cross?"true":"false");

	special.SetNowTime(2, 3, 4);
	ss = special.GetTimeFormatString("l");
	printf("special set after:%s, zone:%d\n", ss.c_str(), special.GetNowTimeZone());
}
#endif
struct DeleteReply
{
	void operator()(redisReply* tp) const
	{
		if(tp != nullptr)
		{
			freeReplyObject(tp);
		}
	}
};
int test_redis(int count, int base)
{
	auto redis_context = redisConnect("192.168.125.25", 6379);
	if(redis_context == nullptr)
	{
		printf("redis_context is nullptr.\n");
		return -1;
	}
	if(redis_context->err != REDIS_OK)
	{
		printf("redis connect failed. err:%d, errstr:%s\n", redis_context->err, redis_context->errstr);
		return -1;
	}
	std::ostringstream os;
	
	for(int i = 0; i < count ; i++)
	{
		os << "hset" << " " << "all_keys" << " " << base + i << " " << "{zone_id=" <<30000+i<<",status=1}";
		if(redisAppendCommand(redis_context, os.str().c_str()) != REDIS_OK)
		{
			ERROR_LOG("[AppendCommand] failed. command_str:%s", os.str().c_str());
			return REDIS_ERR;
		}
		os.str("");
		#if 0
		
		os << "hset" << " " << base + i << " " << "status" << " " << "1";
		if(redisAppendCommand(redis_context, os.str().c_str()) != REDIS_OK)
		{
			ERROR_LOG("[AppendCommand] failed. command_str:%s", os.str().c_str());
			return REDIS_ERR;
		}
		#endif
		for(int k = 0; k < 1; k++)
		{
			void * aux = nullptr;
			if(redisGetReply(redis_context, &aux) != REDIS_OK)
			{
				ERROR_LOG("[redisGetReply] error, err:%d, errstr:%s", redis_context->err, redis_context->errstr);
				//FreeContext();
				return REDIS_ERR;
			}
			redisReply* reply = reinterpret_cast<redisReply*>(aux);	
			if(reply->type == REDIS_REPLY_ERROR)
			{
				ERROR_LOG("[redisGetReply] return REDIS_REPLY_ERROR, errstr:%s", reply->str);
				freeReplyObject(aux);
				return REDIS_ERR;
			}
			if(i % 10000 == 0)
			{
				printf("index:%d\n", i);
			}
			freeReplyObject(aux);	
		}
		
	}
	return 0;
}
int main()
{
	printf("Hello World!\n");
	sds a = sdsnew("abcd");
	sds b = sdscat(a, "eeff");
	printf("b:%s\n", b);
	Init();
	test_redis(10000000, 10);
	getchar();
	return 0;
}
