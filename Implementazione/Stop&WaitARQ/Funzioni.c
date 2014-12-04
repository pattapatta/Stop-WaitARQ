static void transmit_frame(MSG *msg, FRAMEKIND kind,
static void application_ready(CnetEvent ev, CnetTimerID timer, CnetData data)
static void physical_ready(CnetEvent ev, CnetTimerID timer, CnetData data)
static void draw_frame(CnetEvent ev, CnetTimerID timer, CnetData data)
static void timeouts(CnetEvent ev, CnetTimerID timer, CnetData data)
static void showstate(CnetEvent ev, CnetTimerID timer, CnetData data)
void reboot_node(CnetEvent ev, CnetTimerID timer, CnetData data)
