#include "Play_UI.h"

void Play_UI_MgtEntry()
{
    int i, id;
    char choice;

    play_list_t head;
    play_node_t *pos;
    Pagination_t paging;

    List_Init(head, play_node_t);
    paging.offset   = 0;
    paging.pageSize = PLAY_PAGE_SIZE;

    //载入数据
    paging.totalRecords = Play_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);

    do
    {
        printf(
            "\n================================================================"
            "==\n");
        printf(
            "********************** 剧目信息管理界面 "
            "**********************\n");
        printf("%10s  %18s  %10s  %10s  %10s  %10s  %11s    %11s  %5s\n",
               "剧目ID", "剧目名称", "剧目类型", "剧目出品地区", "剧目等级",
               "时长(分钟)", "开始放映日期", "结束放映日期", "票价(元)");
        printf(
            "------------------------------------------------------------------"
            "\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
            printf(
                "%8d  %14s  %8d  %10s  %10d  %10d  %4d年%2d月%2d日  "
                "%4d年%2d月%2d日  %5d\n",
                pos->data.id, pos->data.name, pos->data.type, pos->data.area,
                pos->data.rating, pos->data.duration, pos->data.start_date.year,
                pos->data.start_date.month, pos->data.start_date.day,
                pos->data.end_date.year, pos->data.end_date.month,
                pos->data.end_date.day, pos->data.price);
        }
        printf(
            "------- 总页数:%2d ----------------------- Page "
            "%2d/%2d "
            "----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
        printf(
            "******************************************************************"
            "\n");
        printf(
            "[P]上一页\n"
            "[N]下一页\n"
            "[A]增加新剧目\n"
            "[D]删除剧目\n"
            "[U]修改剧目\n"
            "[Q]查询剧目\n"
            "[S]安排演出\n"
            "[R]返回\n");
        printf(
            "\n================================================================"
            "==\n");

        printf("输入选项:");
        scanf("%c", choice);
        getchar();
        switch (choice)
        {
            case 'a':
            case 'A':
                if (Play_UI_Add() > 0)  //新添加成功，跳到最后一页显示
                {
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, play_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("输入删除剧目id:");
                scanf("%d", &id);
                if (Play_UI_Delete(id) == 1)
                {  //从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("输入需要修改的剧目id:");
                scanf("%d", &id);
                if (Play_UI_Modify(id) == 1)
                {  //从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 's':
            case 'S':
                // printf("输入需要安排演出的放映厅id");
                printf("输入需要安排演出的剧目id\n");
                scanf("%d", &id);

                Schedule_UI_MgtEntry(id);

                paging.totalRecords = Play_Srv_FetchAll(head);
                printf("paging.totalRecords:%d\n", paging.totalRecords);
                List_Paging(head, paging, play_node_t);
                break;
            case 'q':
            case 'Q':
                printf("输入需要查询的剧目id\n");
                scanf("%d", &id);
                Play_UI_Query(id);
                break;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
                }
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("输入有误,请重新输入\n");
                break;
        }
    } while (choice != 'r' && choice != 'R');
    //释放链表空间
    List_Destroy(head, play_node_t);
}
int Play_UI_Add()
{
    printf("\n=======================================================\n");
    printf("****************  增加剧目界面  ****************\n");
    printf("-------------------------------------------------------\n");
    play_t newPlay;
    printf("输入剧目名称\n");
    scanf("%s",newPlay.name);
    if (newPlay.name[strlen(newPlay.name) - 1] == '\n')
        newPlay.name[strlen(newPlay.name) - 1] = '\0';
    while (1)
    {
        printf("输入剧目类型\n");
        printf("1.电影\n2.京剧\n3.音乐会\n");
        int typ;
        scanf("%d", &typ);
        if (typ <= 3 && typ >= 1)
        {
            if (typ == 1) newPlay.type = PLAY_TYPE_FILE;
            if (typ == 2) newPlay.type = PLAY_TYPE_OPEAR;
            if (typ == 3) newPlay.type = PLAY_TYPE_CONCERT;
            break;
        }
        printf("输入有误,请重新输入\n");
    }
    printf("输入剧目出品地区\n");
    scanf("%s", newPlay.area);

    while (1)
    {
        printf("输入剧目等级\n");
        printf("1.小孩\n2.青少年\n3.成人\n");
        if (scanf("%d", (int *)&(newPlay.rating)) == 1 && newPlay.rating >= 1 &&
            newPlay.type <= 3)
        {
            break;
        }
        printf("输入有误,请重新输入\n");
    }
    while (1)
    {
        printf("输入时长(分钟)");
        if (scanf("%d", &newPlay.duration) == 1 && newPlay.duration > 0)
        {
            break;
        }
        printf("输入有误,请重新输入\n");
    }
    while (1)
    {
        user_date_t nowDate = DateNow();
        printf("输入剧目放映日期(年.月.日)");
        if (scanf("%d.%d.%d", &newPlay.start_date.year,
                  &newPlay.start_date.month, &newPlay.start_date.day) == 3 &&
            IsTimeLegal(newPlay.start_date.year, newPlay.start_date.month,
                        newPlay.start_date.day, nowDate.year, nowDate.month,
                        nowDate.day))
        {
            break;
        }
        printf("输入日期有误,请重新输入\n");
    }
    while (1)
    {
        ttms_date_t startDate = newPlay.start_date;
        printf("输入剧目结束日期(年.月.日)");
     
        if (scanf("%d.%d.%d", &newPlay.end_date.year, &newPlay.end_date.month,
                  &newPlay.end_date.day) == 3 &&
            IsTimeLegal(newPlay.end_date.year, newPlay.end_date.month,
                        newPlay.end_date.day, startDate.year, startDate.month,
                        startDate.day))
        {
            break;
        }
        printf("输入日期有误,请重新输入\n");
    }
    while (1)
    {
        printf("输入票价(元)");
        
        if (scanf("%d", &newPlay.price) == 1 && newPlay.price >= 0)
        {
            break;
        }
        printf("输入有误,请重新输入");
    }
    if (Play_Srv_Add(&newPlay))  //文件保存
    {
        printf("添加成功\n");
        return 1;
    }
    else
    {
        printf("添加失败\n");
        return 0;
    }
}
int Play_UI_Modify(int id)
{
    printf("\n=======================================================\n");
    printf("****************  修改剧目界面  ****************\n");
    printf("-------------------------------------------------------\n");
    play_t etc;
    if (!Play_Srv_FetchByID(id, &etc))
    {
        printf("该剧目不存在！");
        return 0;
    }
    else
    {
        play_t newPlay = etc;
        printf("修改剧目名称[%s]=====>", etc.name);
        // fgets(newPlay.name, 30, stdin);
        scanf("%s", newPlay.name);
        if (newPlay.name[strlen(newPlay.name) - 1] == '\n')
            newPlay.name[strlen(newPlay.name) - 1] = '\0';
        while (1)
        {
            char *t = NULL;
            if (etc.type == 1) t = "电影";
            if (etc.type == 2) t = "京剧";
            if (etc.type == 3) t = "音乐会";
            printf("修改剧目类型[%s]=====>\n", t);
            printf("1.电影\n2.京剧\n3.音乐会\n");
            if (scanf("%d", (int *)&newPlay.type) == 1 && newPlay.type >= 1 &&
                newPlay.type <= 3)
            {
                break;
            }
            printf("输入有误,请重新输入\n");
        }
        printf("修改剧目出品地区[%s]=====>\n", etc.area);
        scanf("%s",newPlay.area);
        while (1)
        {
            printf("修改剧目等级[%d]=====>\n", etc.rating);
            printf("1.小孩\n2.青少年\n3.成人\n");
           
            if (scanf("%d", (int *)&newPlay.rating) == 1 &&
                newPlay.rating >= 1 && newPlay.type <= 3)
            {
                break;
            }
            printf("输入有误,请重新输入\n");
        }
        while (1)
        {
            printf("修改剧目时长[%d]=====>", etc.duration);
            if (scanf("%d", &newPlay.duration) == 1 && newPlay.duration > 0)
            {
                break;
            }
            printf("输入有误,请重新输入\n");
        }
        while (1)
        {
            user_date_t nowDate = DateNow();
            printf("修改剧目放映日期(%d.%d.%d)=====>", etc.start_date.year,
                   etc.start_date.month, etc.start_date.day);
           
            if (scanf("%d.%d.%d", &newPlay.start_date.year,
                      &newPlay.start_date.month,
                      &newPlay.start_date.day) == 3 &&
                IsTimeLegal(newPlay.start_date.year, newPlay.start_date.month,
                            newPlay.start_date.day, nowDate.year, nowDate.month,
                            nowDate.day))
            {
                break;
            }
            printf("输入日期有误,请重新输入\n");
        }
        while (1)
        {
            ttms_date_t startDate = newPlay.start_date;
            printf("修改剧目结束日期(%d.%d.%d)=====>", etc.end_date.year,
                   etc.end_date.month, etc.end_date.day);
          
            if (scanf("%d.%d.%d", &newPlay.end_date.year,
                      &newPlay.end_date.month, &newPlay.end_date.day) == 3 &&
                IsTimeLegal(newPlay.end_date.year, newPlay.end_date.month,
                            newPlay.end_date.day, startDate.year,
                            startDate.month, startDate.day))
            {
                break;
            }
            printf("输入日期有误,请重新输入\n");
        }
        while (1)
        {
            printf("修改票价[%d]=====>", etc.price);
           
            if (scanf("%d", &newPlay.price) == 1 && newPlay.price >= 0)
            {
                break;
            }
            printf("输入有误,请重新输入");
        }
        if (Play_Srv_Modify(&newPlay))
        {
            printf("修改成功\n");
            return 1;
        }
        else
        {
            printf("修改失败\n");
            return 0;
        }
    }
}

int Play_UI_Query(int id)
{
    printf("\n=======================================================\n");
    printf("****************  查询剧目界面  ****************\n");
    printf("-------------------------------------------------------\n");
    play_t buf;
    if (Play_Srv_FetchByID(id, &buf) != 1)
    {
        printf("没有查询到相关剧目信息,请确定信息后查询\n");
        return 0;
    }
    printf("%10s  %18s  %10s  %10s  %10s  %10s  %11s    %11s  %5s\n", "剧目ID",
           "剧目名称", "剧目类型", "剧目出品地区", "剧目等级", "时长(分钟)",
           "开始放映日期", "结束放映日期", "票价(元)");
    printf(
        "------------------------------------------------------------------"
        "\n");
    printf(
        "%8d  %14s  %8d  %10s  %10d  %10d  %4d年%2d月%2d日  "
        "%4d年%2d月%2d日  %5d\n",
        buf.id, buf.name, buf.type, buf.area, buf.rating, buf.duration,
        buf.start_date.year, buf.start_date.month, buf.start_date.day,
        buf.end_date.year, buf.end_date.month, buf.end_date.day, buf.price);
    return 1;
}
int Play_UI_Delete(int id) { return Play_Srv_DeleteByID(id); }
