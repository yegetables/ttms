
#define SALESANALYSIS_PAGE_SIZE 5
/**
 * @brief 管理售票主界面
 */
void Sale_UI_MgtEntry(void);

/**
 * @brief 根据剧目id显示演出计划
 * @param playID int剧目id
 */
void Sale_UI_ShowScheduler(int playID);

/**
 * @brief 售票
 * @param tickList 票列表
 * @param seatList 座位列表
 * @return int 售出票的座位id
 */
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList);



/**
 * @brief 退票
 */
void Sale_UI_RetfundTicket(void);

















void Sale_UI_ShowTicket(int playID);