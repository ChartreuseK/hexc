#ifndef OFFSETBAR_H
#define OFFSETBAR_H



class OffsetBar {
	public:
		OffsetBar(const chtype attr, WINDOW *win);
	
	private:
		chtype ncAttr;
		WINDOW *win;
}


#endif
