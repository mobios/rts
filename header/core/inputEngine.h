
struct core::clickable{
};

typedef void (clickable::* mhandler)();
typedef void (* handler)();

namespace core{
	struct keyHandler{
		handler callback;
		unsigned int key;
	};
	
	struct mouseHandler{
		mhandler callback_over;
		mhandler callback_out;
		mhandler callback_down_l;
		mhandler callback_up_l;
		mhandler callback_down_r;
		mhandler callback_up_r;
		float x;
		float y;
		float xsize;
		float ysize;
	};
	
	struct inputEngine{
		static void postMsg();
		static void registerHandler(void (*)())