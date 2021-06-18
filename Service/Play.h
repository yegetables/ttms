#ifndef PLAY_H_
#define PLAY_H_

//剧目类型定义
typedef enum
{
    PLAY_TYPE_FILE    = 1,
    PLAY_TYPE_OPEAR   = 2,
    PLAY_TYPE_CONCERT = 3
} play_type_t;

//剧目分级定义
typedef enum
{
    PLAY_RATE_CHILD   = 1,
    PLAY_RATE_TEENAGE = 2,
    PLAY_RATE_ADULT   = 3
} play_rating_t;

// //日期结构体
// typedef struct
// {
//     int year;
//     int month;
//     int day;
// } user_date_t, ttms_date_t;

// //时间结构体
// typedef struct
// {
//     int hour;
//     int minute;
//     int second;
// } user_time_t, ttms_time_t;

//剧目实体数据类型定义
typedef struct
{
    int id;                  //剧目ID
    char name[31];           //剧目名称
    play_type_t type;        //剧目类型
    char area[9];            //剧目出品地区
    play_rating_t rating;    //剧目等级
    int duration;            //时长,以分钟为单位
    ttms_date_t start_date;  //开始放映日期
    ttms_date_t end_date;    //结束放映日期
    int price;               //价格
    // char describe[100];  //剧目描述
} play_t;

//剧目链表定义
typedef struct play_node
{
    play_t data;
    struct play_node *next;
    struct play_node *prev;
} play_node_t, *play_list_t;

/**
 * @brief 获取全部剧目
 *
 * @param list 存剧目的链表头
 * @return int 返回值:剧目数量
 */
int Play_Srv_FetchAll(play_list_t list);

/**
 * @brief 添加新剧目
 *
 * @param data 新剧目的信息
 * @return int 返回值==1添加成功,!=1添加失败
 */
int Play_Srv_Add(play_t *data);

/**
 * @brief 修改剧目
 *
 * @param data 指向待修改的剧目信息
 * @return int 返回值==1修改成功,!=1修改失败
 */
int Play_Srv_Modify(const play_t *data);

/**
 * @brief 删除剧目
 *
 * @param id 根据剧目id删除剧目
 * @return int 返回值==1删除成功,!=1删除失败
 */
int Play_Srv_DeleteByID(int id);

/**
 * @brief 根据剧目ID获取剧目信息
 *
 * @param id 剧目id
 * @param buf buf保存获取剧目的内存地址
 * @return int 返回值==1获取成功,!=1获取失败
 */
int Play_Srv_FetchByID(int id, play_t *buf);
/**
 * @brief 根据剧目name获取剧目信息
 * @param name 剧目name
 * @param buf buf保存获取剧目的内存地址
 * @return int 返回值==1获取成功,!=1获取失败
 */
int Play_Srv_FetchByName(char *name, play_t *buf);
/**
 * @brief 通过剧目关键字模糊查询剧目
 *
 * @param list 存储含有关键字的剧目链表头指针
 * @param key 剧目名关键字
 * @return int 含有关键字的剧目数量
 */
int Play_Srv_FilterByName(play_list_t list, char *key);
#endif
