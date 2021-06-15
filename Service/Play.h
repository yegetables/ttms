#ifndef PLAY_H
#define PLAY_H
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

//日期类型定义
typedef struct
{
    int year;
    int month;
    int day;
} ttms_date_t;

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
    int price;
    // char describe[100];  //剧目描述
} play_t;

//剧目链表定义
typedef struct play_node
{
    play_t date;
    struct play_node *next;
    struct play_node *prev;
} play_node_t, *play_list_t;

//获取全部剧目,返回值:剧目数量
int Play_Srv_FetchAll(play_list_t list);

//添加新剧目,返回值==1添加成功,!=1添加失败
int Play_Srv_Add(play_t *data);

//修改剧目,返回值==1修改成功,!=1修改失败
int Play_Srv_Modify(const play_t *data);

//删除剧目,根据剧目id删除剧目,返回值==1删除成功,!=1删除失败
int Play_Srv_DeleteByID(int id);

//获取剧目,根据剧目ID获取剧目信息,返回值==1获取成功,!=1获取失败,buf保存获取剧目的内存地址
int Play_Srv_FetchByID(int id, play_t *buf);
#endif