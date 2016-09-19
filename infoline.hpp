#ifndef INFOLINE_HPP
#define INFOLINE_HPP


class InfoLine {
	public:
		InfoLine(const chtype attr, WINDOW *win);
		void redraw();
	private:
		chtype ncAttr;
		WINDOW *win;
};

#endif
