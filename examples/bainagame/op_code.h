#ifndef MUDUO_EXAMPLES_BAINAGAME_OP_CODEC_H
#define MUDUO_EXAMPLES_BAINAGAME_OP_CODEC_H


#define GLOBAL_OPCODE_MSG_NULL_ACTION         0x0000

#define GLOBAL_OPCODE_CMSG_ECHO               0x0001
#define GLOBAL_OPCODE_SMSG_ECHO               0x0002

#define GLOBAL_OPCODE_CMSG_PING               0x0003
#define GLOBAL_OPCODE_SMSG_PONG               0x0004

#define GLOBAL_OPCODE_CMSG_HELLO_SERVER       0x0005
#define GLOBAL_OPCODE_SMSG_HELLO_CLIENT       0x0006

enum GAME_OPCODE
{
	MSG_NULL_ACTION							= GLOBAL_OPCODE_MSG_NULL_ACTION,

	CMSG_ECHO 								= GLOBAL_OPCODE_CMSG_ECHO, // for performance test
	SMSG_ECHO 								= GLOBAL_OPCODE_SMSG_ECHO, // for performance test

	//Ping/Pong
	CMSG_PING                               = GLOBAL_OPCODE_CMSG_PING,
	SMSG_PONG                               = GLOBAL_OPCODE_SMSG_PONG,

	CMSG_HELLO_SERVER                       = GLOBAL_OPCODE_CMSG_HELLO_SERVER,
	SMSG_HELLO_CLIENT                       = GLOBAL_OPCODE_SMSG_HELLO_CLIENT,


	//==��¼���Э�酷	
	SMSG_KICK	= 31,		//���ӳ�������	CMSG_BYE,
	SMSG_KEEP_ACTIVE,	//��������

	CMSG_ACCOUNT_LOGIN,		//�˺ŵ�¼
	SMSG_LOGIN_RESP,		//�˺ŵ�¼����

	CMSG_CHECK_NAME,		//����؅�	SMSG_CHECK_NAME_RESP,		//�����������
	CMSG_ACCOUNT_REGISTER,		//���ע���˺�
	SMSG_ACCOUNT_REGISTER_RESP,		//���ע���˺ŷ���

	CMSG_THIRD_BIND,		//�������˺Ű���	SMSG_THIRD_BIND_RESP,		//�������˺Ű󶨷��e
	CMSG_THIRD_LOGIN,		//�������˺ŵ��	SMSG_THIRD_LOGIN_RESP,		//�������˺ŵ�½���e
	CMSG_ACCOUNTINFO_MOD,	//�˺���Ϣ�޸�modify
	SMSG_ACCOUNTINFO_MOD_RESP,

	SMSG_PLAYER_INFO,	//�˺���Ϣgameserver -> client

	CMSG_PLAYER_GET_SPREE,	// ��ȡ���� =>
	SMSG_PLAYER_GET_SPREE_RESP,		// <= (errorCode, next time)

	CMSG_ACCOUNT_LOGOUT,	//�˺ŵǳ�
	SMSG_LOGOUT_RESP,

	CMSG_OPTIONS,			// ������������	SMSG_OPTIONS_RESP,

	CMSG_ACCOUNT_TYPE,		// �˺����� =>		# ����û���Ϣ�󣬷����˺����͸������?
	CMSG_ACCOUNT_PASSWORD_RESET, // ��������?	SMSG_ACCOUNT_PASSWORD_RESET_RESP,  //�������÷���ֵ?
	SMSG_ACCOUNT_AVATAR_UPDATED, // ͷ���޸�֪ͨ?<= (struct stAvatarInfo)

	SMSG_CONFIG_RESP, // ��������������<= (struct GM2C_Config_Resp)

	CMSG_SERVER_CONFIG=58, //���·�������ַ <= (struct C2GM_ServerConfig )
	SMSG_SERVER_CONFIG_RESP,

	//==���������]	CMSG_ROOM_GET_LIST = 101,	//��ȡĳ���͵ķ����б�
	SMSG_ROOM_GET_LIST_RESP,
	CMSG_ROOM_PLAYER_ENTER,	//ѡ������˷��]	SMSG_ROOM_PLAYER_ENTER_RESP,
	CMSG_HALL_INFO,			// ���������Ϣ
	SMSG_HALL_INFO_RESP,	// ������Ϣ
	CMSG_HALL_QUICK_START,			// ���ٿ�ʼ��T	# (roomType) =>	
	SMSG_HALL_QUICK_START_RESP,		// ���ٿ�ʼ�Ľ��	# <= (errorCode, uRoomID)

	CMSG_ROOM_GET_TOP_MATCH_POINT_PLAYERS, // ���󷿼������ߵ��û�;
	SMSG_ROOM_GET_TOP_MATCH_POINT_PLAYERS_RESP, // ���󷿼������ߵ��û��Ľᖨ	SMSG_ROOM_MATCH_POINT_RESET_EVENT, // ����������Ϣ
	SMSG_ROOM_RANK_UPDATE, // ��������
	// !!!:SMSG_RESTORE_GAME/CMSG_RESTORE_GAME_RESP are not used
	// Use CMSG_RESUME_GAME/SMSG_RESUME_GAME_RESP instead
	SMSG_RESTORE_GAME,		// (MatchID, RooomID, TableID) <= ��Ϸ��������
	CMSG_RESTORE_GAME_RESP, // (bool accept) => ��Ϸ��������������Ϣ��ȷ���Ƿ�����?	CMSG_RESUME_GAME,		// (struct stGameResumeReq) =>	# ��ͼ�ָ���Ϸ      ��������
	SMSG_RESUME_GAME_RESP,	// (struct stGameResumeResp) <=	# �ָ���Ϸ��� ��������

	CMSG_CREATE_TABLE,		// CG_CreateRoom (MatchID, RoomTypeID) => ����һ�����䣨Ŀǰ�Friend ˽�˷���
	SMSG_CREATE_TABLE_RESP,	// GC_CreateRoomResp (MatchID, RoomTypeID, RooomID, TableID, {extras}) <= �������ӵķ���	CMSG_PLAYER_ENTER_TABLE2,	// GC_EnterTableEx (MatchID, RoomTypeID, extras) => ��ҽ�������

	//==����
	CMSG_TABLE_GET_LIST,		//��ȡ�����б�
	SMSG_TABLE_GET_LIST_RESP,
	CMSG_TABLE_PLAYER_ENTER,	//ѡ���������
	SMSG_TABLE_PLAYER_ENTER_RESP,
	SMSG_PLAYER_TABLE_INFO = 201,	//���ӵ���Ϣ���͸����
	SMSG_PLAYER_ON_TABLE_BROADCAST,//�ҽ����˸����\	SMSG_PLAYER_TABLE_DEALER,	//˭��ׯ��
	CMSG_PLAYER_TABLE_READY,	//׼������
	SMSG_PLAYER_TABLE_READY_BROADCAST,
	CMSG_PLAYER_TABLE_BASE_ANTE,	//��ע
	SMSG_PLAYER_TABLE_BASE_ANTE_BROADCAST,
	SMSG_PLAYER_TABLE_DEAL,//����
	CMSG_PLAYER_TABLE_ANTE,	//��ע
	SMSG_PLAYER_TABLE_ANTE_RSP,//��ע����
	SMSG_PLAYER_TABLE_ANTE_BROADCAST,
	SMSG_PLAYER_TABLE_ANTE_COUNT_BROADCAST,	//������Ǯ����	CMSG_PLAYER_TABLE_LOOK_POKER,	//����
	SMSG_PLAYER_TABLE_LOOK_POKER,
	SMSG_PLAYER_TABLE_LOOK_POKER_BROADCAST,
	CMSG_PLAYER_TABLE_COMPARE,	//����
	SMSG_PLAYER_TABLE_COMPARE_RSP,
	SMSG_PLAYER_TABLE_COMPARE_BROADCAST,
	CMSG_PLAYER_TABLE_GIVEUP,	//����
	SMSG_PLAYER_TABLE_GIVEUP_BROADCAST,
	SMSG_PLAYER_TABLE_GAME_OVER_BROADCAST,	//���ֽ���
	CMSG_PLAYER_LEAVE_TABLE,		//�뿪����
	SMSG_PLAYER_KICKED_FROM_TABLE,	//��ұ��������\	SMSG_PLAYER_LEAVE_TABLE_BROADCAST,	//֪ͨ�����ڵ���<= (PlayerID, ePlayerLeaveRoomReason)
	CMSG_PLAYER_CHANGE_TABLE,	//��һ���?	SMSG_PLAYER_CHANGE_TABLE_RSP,
	SMSG_PLAYER_ACTIVE_PLAYER,	//��ǰ����
	CMSG_PLAYER_TABLE_CURR_ANTE,//��ǰע��
	SMSG_PLAYER_TABLE_CURR_ANTE,//�㲥��ǰע��
	SMSG_PLAYER_TABLE_ACTIVE_TIMEOUT,	//�ʱ����	SMSG_PLAYER_TABLE_COUNTDOWN_BEGIN,	//����ʱʮ�뿪��	SMSG_PLAYER_MONEY_CHANGE,	//��ҵ�Ǯ�仯
	SMSG_PLAYER_POINT_UPDATE,	//==��ҵĽ�ɫ���ֱ���	SMSG_PLAYER_TABLE_ROUNDS_CHANGE,	//�غϱ仯
	SMSG_PLAYER_TABLE_POINT_CHANGE,	//���ֻ��ֱ仯
	SMSG_PLAYER_TABLE_MATCH_ROUNDS,	//�����֔�	SMSG_PLAYER_TABLE_GAME_BEGIN_BROADCAST, // (SessionID) <= # ������Ϸ��ʼ����	CMSG_PLAYER_TABLE_DEALER_DEAL_FINISHED, // (SessionID) => # ׯ�ҵķ����귿	SMSG_PLAYER_TABLE_SYSTEM_NOTIFY,							// <= (nType, sMsg, uReserved)				# ����֪ͨ
	CMSG_PLAYER_TABLE_FOLLOW_ALLTIME,							// (nAction) =>				# ������ ��Ӳ��� nAction=1�������� 2��ȡ��������
	SMSG_PLAYER_TABLE_PLAYER_ONLINE_STATUS_CHANGED_BROADCAST,	// <= (PlayerID, Status)	# ��Ҷ��� Status=ONLINE_STATUS_ONLINE: Online, ONLINE_STATUS_OFFLINE:Offline
	SMSG_PLAYER_TABLE_FOLLOW_ALLTIME_BROADCAST,					// <= (PlayerID, nAction)	# ��Ҹ����׻���ȡ��������
	SMSG_PLAYER_TABLE_INFO_SYNC,			// ͬ��ˢ�����Ӻ���ҵ�״̬����(struct GC_TableInfo)
	SMSG_PLAYER_TABLE_COINS_WARNING,		// ���Ԥ��
	SMSG_PLAYER_TABLE_GAME_PRIZE_INFO,		// ��Ϸ������Ϣ?
	SMSG_PLAYER_TABLE_DEALER_DEAL_BROADCAST,// <=	# ��ʼ���ƵĹ㲥
	CMSG_PLAYER_TABLE_CHANGE_CARD,			// [index] =>		# ����
	SMSG_PLAYER_TABLE_CHANGE_CARD_RESP,		// <= (Result, [card])	# �Լ����Ƶķ��e	SMSG_PLAYER_TABLE_CHANGE_CARD_BROADCAST,// [index] =>		# ���ƵĹ��	
	SMSG_PLAYER_DIMONDS_CHANGE,
    SMSG_PLAYER_TABLE_INFO_MJ1V1,

	CMSG_PLAYER_END = 400,

	// ����������	SMSG_PLAYER_TABLE_INVITE = 401,	// <= (MatchID, RoomType, RooomID, TableID) # �����������������ҽ�������
	CMSG_PLAYER_ENTER_TABLE,		// (MatchID, RoomType, RooomID, TableID) =>	# �����˽�����������ض����\	SMSG_PLAYER_ACTION_SUGGEST,		// <= (Suggest)								# ��������˲�ȡ��������	SMSG_PLAYER_SET_STRATEGY,		// <= (Strategy)							# �������޸���Ӯ����	SMSG_PLAYER_HANDS,				// <= ({PlayerID => Pokers})				# ���ƴ�С��ȫ���˵�����

	// ��Ϣ��֪ͨ
	SMSG_MESSAGE_NEW = 501, // <= �յ�������(struct GC_Message_List)
	CMSG_MESSAGE_LIST, // => ��ȡ��Ϣ
	SMSG_MESSAGE_LIST_RESP, // <= ������Ϣ����ʱ������ (struct GC_Message_List)
	CMSG_MESSAGE_SEND, // => ��������	SMSG_MESSAGE_SEND_RESP , // <= ������Ϣ״��	SMSG_NOTIFICATION_SEND,  //����֪ͨ

    //���书��
    CMSG_MESSAGE_LIST_EX,
    SMSG_MESSAGE_LIST_RESP_EX,
    CMSG_MESSAGE_UPDATE_STATUS,
    SMSG_MESSAGE_UPDATE_STATUS_RESP,


	//��Ϣ���T	CMSG_PLAYER_PUSH_ID = 581,	//�ύaccId��DeviceId (struct C2GM_PlayerPushID)
	CMSG_PUSH_TO_PLAYER,

    CMSG_GM_GET_PLAYER_STATUS=600,
    SMSG_GM_GET_PLAYER_STATUS_RESP,
    CMSG_GM_SEND_MESSAGE,
    SMSG_GM_RECV_MESSAGE,
    SMSG_GM_SEND_MESSAGE_RESP,

	// ����
	CMSG_PLAYER_SETTINGS_UPDATE = 700,			//	<= (int32 settings)		# ������Ϣ���õĽ��
	SMSG_PLAYER_SETTINGS_UPDATE_RESP,			//  => (errorCode)			# ��Ϣ���õĽᖨ
    CMSG_PLAYER_SETTING_SEX = 701,              //         #�����Ա�����
    SMSG_PLAYER_SETTING_SEX_RESP,               //         #�Ա����õĽᖨ
	// �̵��֧��	CMSG_SHOP_GET_LIST = 1001,		// =>						# ������Ʒ�б�
	SMSG_SHOP_GET_LIST_RESP,		// <= ��Ʒ�б�				# ������Ʒ�б�
	CMSG_SHOP_BUY_ITEM,				// ��ƷID =>				# ��������Ʒ
	SMSG_SHOP_BUY_ITEM_RESP,		// <= ƽ̨,������		# ���ض�����
	SMSG_SHOP_ORDER_RESULT,			// <= �������				# ���ض������, ������ҽ��

	CMSG_SHOP_ROBOT_BUY_ITEM,		// ��Ʒ��Ϣ =>				# �����˹����ض���Ʒ��ֱ�Ӽӽ�ң��������Ǐ�	SMSG_SHOP_ROBOT_BUY_ITEM_RESP,	// <= �ɹ� or ʧ��			# ���ػ����˹����ض���Ʒ�Ľ��

	CMSG_SHOP_UPDATE_LIST,			// [(ver, platform)] =>	    # ���������Ʒ�б�
	SMSG_SHOP_UPDATE_LIST_RESP,		// <= [(ver, platform, {updates}]
									//							# ��Ʒ�б����?
	CMSG_SHOP_CLIENT_COMPLETE_ORDER,// ƽ̨,���������(CMSG_CompleteShopOrder)	# �ͻ��˸�֪�û���ɶ���?	CMSG_SHOP_CLIENT_COMPLETE_ORDER_RESP,

    SMSG_HORN_DETIAL,                // ����֧����ʽ�ͼۖ�
	// ���И�	CMSG_CHART_GET = 1101,			// (chart_id, from, to) =>	# ��ȡ�ض��񵥵����		
	SMSG_CHART_GET_RESP,			// <= (count, [<csv>])		# ���ذ���Ϣ

    // ������а�ָ��    SMSG_RANK_CHAMPION,             //���ͽ��������И�	SMSG_CHART_GET_PERONAL_INFO_IN_RANK_RESP=1107,//1107 ���ذ����������	// ������	CMSG_HONOR_ROOM_GET_LIST = 1201,// =>
	SMSG_HONOR_ROOM_GET_LIST_RESP,	// =>
	// TODO: ���������ָ��
  GL_PERSONAL_INFO_IN_RANK,//1203
	//�������л�����Ϣ
	CMSG_TASK_ALL = 1301,
	SMSG_TASK_ALL_RESP,
	//���������Ϣ
	CMSG_PLAYER_TASK_STATE,
	SMSG_PLAYER_TASK_STATE_RESP,
	//���������Ϣ�仯
	SMSG_PLAYER_NEW_TASK,
	//��������콱
	CMSG_PLAYER_TASK_REWARD,
	SMSG_PLAYER_TASK_REWARD_RESP,
    //�ƹ�app ���� 
    CMSG_TASK_APP_DOWNLOAD,
    SMSG_TASK_APP_DOWNLOAD_RESP, 
    CMSG_TASK_APP_DOWNLOAD_COMPLETE,
    SMSG_TASK_APP_DOWNLOAD_COMPLETE_RESP,
	//share����
	CMSG_REQUEST_SHARE_INFO,
	SMSG_REQUEST_SHARE_INFO_RESP,

	// �������
	CMSG_RAFFLE_GET_RAFFLE = 1401,	// ��ȡ��ȯ
	CMSG_RAFFLE_GET_DRAWLIST,	// ��ȡ��Ʒ�б�
	SMSG_RAFFLE_GET_DRAWLIST_RESP,
	CMSG_RAFFLE_GET_DRAWID,   // ��ȡһ����ƷID
	SMSG_RAFFLE_GET_DRAWID_RESP,

	CMSG_LOTTERY_BUY_LOTTERY = 1501,	// �����Ʊ
	SMSG_LOTTERY_BUY_LOTTERY_RESP,
	SMSG_LOTTERY_GET_LOTTERY_MONEY, // �н�
	CMSG_LOTTERY_GET_LOTTERY_HOTNUMBER, // ��ȡ���ź���
	SMSG_LOTTERY_GET_LOTTERY_HOTNUMBER_RESP,
	CMSG_LOTTERY_GET_LOTTERY_TOPHISTORY, // ��ȡ���׼�¼
	SMSG_LOTTERY_GET_LOTTERY_TOPHISTORY_RESP,
	CMSG_LOTTERY_GET_LOTTERY_INFO,	// ��ȡ��Ʊ��Ϣ���������أ��Ϳ���ʱ�䣬������������ǰ��½��ҹ���ĺ���ͱ���������û�й���Ϊ�㣩
	SMSG_LOTTERY_GET_LOTTERY_INFO_RESP,
	CMSG_LOTTERY_GET_LAST_WINHISTORY, // �����ȡ�����н�����
	SMSG_LOTTERY_GET_LAST_WINHISTORY_RESP, 
	CMSG_LOTTERY_GET_PREVIOUS_INFO,			// =>									# ��ȡ��һ�ڲ�Ʊ���	SMSG_LOTTERY_GET_PREVIOUS_INFO_RESP,	// <= (�ں�,�н�����,ע��,�н����) 	# ��һ���Լ����н����

	// ����
	CMSG_FEEDBACK = 2001,			// feedback msg =>			# ���ͷ��e	SMSG_FEEDBACK_RESP,				// <= (result)				# �����Ľᖨ
	CMSG_CAMPAIGN_GET_LIST = 2011,	// (timestamp) =>			# ��ȡ���Ϣ
	SMGS_CAMPAIGN_GET_LIST_RESP,	// <= (count, [campaign])	# ���ػ�б�

	CMSG_DAILYLOGIN,
	SMGS_DAILY_RESP,	// ������½������
	// ��ȡ����
	CMSG_UPATA_CONFIG,			//
	SMSG_UPATA_CONFIG_RESP,			//

	//�����д������
	CMSG_INVITED = 2021,
	SMSG_INVITED_RESP,

	// ��ѯ/��Ӧ�Ƽ���������
	CMSG_INVITED_CONTENT,
	SMSG_INVITED_CONTENT_RESP,

	//==����ģ��

	//ҡǮ��	CMSG_MONEYTREE_INFO = 2031,	// ҡǮ������	SMGS_MONEYTREE_INFO_RESP,	

	CMSG_MONEYTREE_ROCK,		// ҡǮ������	SMGS_MONEYTREE_ROCK_RESP,

    //Slots
    CMSG_SLOTS_ENTER =2035,								//2035 �ϻ���������T    SMSG_SLOTS_ENTER_RESP,							//2036 �ϻ����������    CMSG_SLOTS_START,								//2037 �ϻ�����ʼ��T    SMSG_SLOTS_START_RESP,							//2038 �ϻ�����ʼ���    CMSG_SLOTS_COMPARE,								//2039 �ϻ���������T
    SMSG_SLOTS_COMPARE_RESP,						//2040 �ϻ����������    CMSG_SLOTS_HARVEST,								//2041 �ϻ����շ���T    SMSG_SLOTS_HARVEST_RESP,						//2042 �ϻ����շ����    CMSG_SLOTS_QUIT,								//2043 �ϻ����˳���T    SMSG_SLOTS_QUIT_RESP,							//2044 �ϻ����˳����    SMSG_SLOTS_UPDATE,								//2045 �ϻ�������ˢ��    CMSG_SLOTS_RESUME,                              //2046 �ϻ���������T
    SMSG_SLOTS_RESUME_RESP,                         //2047 �ϻ����������    CMSG_SLOTS_CHANGE,                              //2048 �ϻ���������T
    SMSG_SLOTS_CHANGE_RESP,                         //2049 �ϻ����������    CMSG_PLAYER_SLOTS_RANK,							//2050 �ϻ����н�������Ϣ��T    SMSG_PLAYER_SLOTS_RANK_RESP,						//2051 �ϻ����н�������Ϣ����
    //�һ�ϵͳ
    CMSG_REWARD_GET_PERSONAL_INFO = 2100, //�õ��û������� 
    SMSG_REWARD_GET_PERSONAL_INFO_RESP, 
    CMSG_REWARD_GET_REWARD_INFO,              //�õ��һ���Ʒ������ 
    SMSG_REWARD_GET_REWARD_INFO_RESP, 
    CMSG_REWARD_PURCHASE_BY_COUPON,           //��Ҷһ�����  
    SMSG_REWARD_PURCHASE_BY_COUPON_RESP,

	//����ϵͳ
	CMSG_PLAYER_LIST_INFO = 3001,	// ����б�
	SMSG_PLAYER_LIST_INFO_RESP,	
	CMSG_PLAYER_ENTER_CAISHEN_TABLE, // ��ҽ��뷿��
	SMSG_PLAYER_ENTER_CAISHEN_RESP,	
	CMSG_PLAYER_LEAVE_CAISHEN_TABLE, // ����뿪����
	SMSG_PLAYER_LEAVE_CAISHEN_RESP,	
	SMSG_PLAYER_START_ANTE_CAISHEN_TABLE_BROADCAST,// ��ʼ��ע���	CMSG_PLAYER_ANTE_CAISHEN_TABLE,	// ��ע	
	SMSG_PLAYER_ANTE_CAISHEN_RESP,	
	SMSG_PLAYER_OPEN_WINNING_COUNTDOWN_BEGIN_BROADCAST, // ��������ʱ���	CMSG_PLAYER_ANTE_INFO, // ��ѯ��ע��Ϣ
	SMSG_PLAYER_ANTE_INFO_RESP,
	SMSG_PLAYER_RESULT_INFO_RESP,		//���i	SMSG_PLAYER_CHARTS_TOP_RESP,		//���а�topN
	CMSG_PLAYER_CHARTS_FROM_TO,			//���И�	SMSG_PLAYER_CHARTS_FROM_TO_RESP,
	CMSG_CAISHEN_PLAYER_RESUME_GAME,	//
	SMSG_CAISHEN_PLAYER_RESUME_GAME_RESP, // (SMSG_PlayerResumeGameInCaiShen_Resp)
	SMSG_PLAYER_ANTE_CAISHEN_INFO_RESP,	//���Ѻע���, ���ڶ��ߺ�ָ�Ѻ��	// ˽�ˈ]
	SMSG_PLAYER_START_SET_WINNING_CAISHEN_TABLE_BROADCAST, // ��ʼ���ÿ�������Ϊ������������>=2���ܿ�ʼ��	
	SMSG_PLAYER_CANCEL_START_SET_WINNING_CAISHEN_TABLE_BROADCAST, // ȡ�����ÿ�������Ϊ������������>=2���ܿ�ʼ��	
	CMSG_PLAYER_SET_WINNING_CAISHEN_TABLE,	// ���ÿ��i	SMSG_PLAYER_SET_WINNING_CAISHEN_TABLE_RESP,	

	//�齫
	CMSG_PLAYER_ENTER_MAHJONG_TABLE_REQ = 4001,//�ͻ��˷�����ҽ������ӵ�����
	CMSG_PLAYER_MAHJONG_TABLE_READY_REQ,//�ͻ��˷������׼����T	CMSG_PLAYER_CHANGE_MAHJONG_TABLE_REQ,//�ͻ��˷�����һ�����T	CMSG_PLAYER_LEAVE_MAHJONG_TABLE_REQ,//�ͻ��˷������������T
	CMSG_PLAYER_MAHJONG_ACTION,//�ͻ��˷������ִ�еĶ���
	CMSG_PLAYER_MAHJONG_DISCARD,//�ͻ��˷�����Ҵ������	
	SMSG_MAHJONG_BANKER_INFO_BROADCAST,//�������㲥ׯ�Һ�������Ϣ
	SMSG_MAHJONG_HANDMAHJONG_INFO,//���������������������	SMSG_MAHJONG_ACTION_RESP,//����������Ҷ����Ļ؎�	SMSG_MAHJONG_ACTION_BROADCAST,//�������㲥ĳ���ִ�еĶ�ʹ	SMSG_MAHJONG_ACTIVEPLAYER_BROADCAST,//�������㲥��ǰ��Ծ����	SMSG_PLAYER_MAHJONG_DEAL,//����������ҷ�������
	SMSG_MAHJONG_DISCARD_MAHJONG_BROADCAST,//�������㲥ĳ����Ҵ������	SMSG_MAHJONG_PLAYER_ACTION_ASK,//��������Ҷ���ѯ�]	SMSG_MAHJNG_GAMERESULT_BROADCAST,//��Ϸ����㲥
	SMSG_MAHJONG_NUMBER_BROADCAST,//�ͻ��˹㲥��ǰʣ���Ɣ�	CMSG_PLAYER_MAHJONG_TUOGUAN_REQ,//�ͻ��������й�	CMSG_PLAYER_MAHJONG_CANCLE_TUOGUAN_REQ,//�ͻ�������ȡ���й�	SMSG_PLAYER_MAHJONG_TUOGUAN_RES,//��ͻ��˸�����Ӧ
	SMSG_PLAYER_MAHJONG_CANCLE_TUOGUAN_RES,//��ͻ��˸���ȡ���йܻ�Ӧ
	SMSG_PLAYER_MAHJONG_QUICKSTART_REQ,//�齫�ͻ��˿��ٿ�ʼ��T    SMSG_PLAYER_MAHJONG_TEST_GET_FIXED_CARD_REQ,    //������ѯ�ʿͻ��ˣ���ȡָ�����齫
    SMSG_PLAYER_MAHJONG_TEST_GET_FIXED_CARD_ANS,    //�ͻ���Ӧ�𣬻�ȡָ��������    SMSG_LISTEN_HELP,                               //������ʾ����ʾ��ҳ���Щ�ƺ󣬿�������    SMSG_HAS_LISTENNED_CARD,                        //������ʾ����ʾ��ҿ��Ժ���Щ��    SMSG_GET_CARDS_TING_INFO_WHEN_3N1,              //�����������دn+1��ʱ�򣬲鿴������ʾ��Ϣ
    SMSG_PLAYER_MAHJONG_LIANGDAO_ASK,               //ѯ������Ƿ���������    CMSG_PLAYER_MAHJONG_LIANGDAO_ANS,               //����������ƺ�����    SMSG_PLAYER_MAHJONG_LIANGDAO_BROADCAST,         //�㲥���������������    SMSG_PLAYER_MAHJONG_GANG_RESULT,                //��Ҹ��ƽ�����Ϣ
    SMSG_PLAYER_MAHJONG_TABLE_CREATE_REQ,           //�����齫���ӵ�����Э��    SMSG_PLAYER_MAHJONG_TABLE_CREATE_ANS,           //�����齫���ӵ�����Э��    SMSG_PLAYER_MAHJONG_TABLE_PWD_CHECK_REQ,        //��������������ǰ������У����T    SMSG_PLAYER_MAHJONG_TABLE_PWD_CHECK_ANS,        //��������������ǰ������У�����    SMSG_PLAYER_MAHJONG_KICK_PLAYER_REQ,            //�����ҷ���������T    SMSG_PLAYER_MAHJONG_KICK_PLAYER_ANS,            //�����ҷ����������    SMSG_PLAYER_MAHJONG_TABLE_INFO_CHANGE_BROADCAST,    //������Ϣ�ı�㲥��Ϣ
	CMSG_PLAYER_EXCHANGE_RATE_INFO_REQ,             // �ͻ���������Ʒ�һ��б���T    SMSG_PLAYER_EXCHANGE_RATE_INFO,                 // ��Ʒ�һ��б���Ϣ
    CMSG_PLAYER_GET_GOLDCOINS_BY_DIAMONDS_REQ,      // �ͻ���������ʯ��������T	SMSG_PLAYER_GET_GOLDCOINS_BY_DIAMONDS_ANS,      // ��ʯ������Ӧ��
	SMSG_PLAYER_MAHJONG_SYC_TABLE_DETAIL_INFO,      //ͬ��������ϸ��Ϣ�����������������Ժ��T    SMSG_PLAYER_ENTER_OR_LEAVE_CARDROOM_NOTIFY,     //֪ͨ��������ҽ�������뿪������    SMSG_PLAYER_MAHJONG_PLAYER_SESSION_STATE_BROADCAST,     //ͬ���������״��    CMSG_PRESENT_INFO,                              // ����˵�ҳ������ť(������Ҫ�ж�����Ƿ���Ȩ�ޣ�
    SMSG_PRESENT_INFO_RESP,
    CMSG_PRESENT_ACCOUNT_CHECK,                     // �������Է���������ȷ�ϣ���Ҫ��ȡ�Է��ǳƣ�
    SMSG_PRESENT_ACCOUNT_CHECK_RESP,
    CMSG_GIVE_PRESENT,                              // ���ȷ���ͽ���    SMSG_GIVE_PRESENT_RESP,
    SMSG_PLAYER_ENTER_ROOM_RECHARGE,                // ���뷿��ʱûǮ����ͻ������͵ĳ�ֵ����    SMSG_PLAYER_PUSH_PROMPT_MSG,                    // ����һ��������Ϣ���ͻ��ˣ��Ա�����
	SMSG_MAHJONG_ACTION_RATE_RESP,					// ������������Ҷ���rate��Ϣ
	SMSG_MAHJONG_ACTION_RATE_BROADCAST,				// �������㲥��Ҷ���rate��Ϣ
	SMSG_MAHJONG_TABLE_READY_STATE_BROADCAST,		// �������㲥�������׼��״������׼��or׼��)
	CMSG_PLAYER_GET_SIGNED_PANEL_INFO,				// ��ҽ���ǩ���������
	SMSG_PLAYER_GET_SIGNED_PANEL_INFO_RSP,			// ��ҽ���ǩ�������Ӧ
	CMSG_PLAYER_SIGNED,								// ���ǩ��
	SMSG_PLAYER_SIGNED_RSP,							// ���ǩ����Ӧ
    CMSG_PLAYER_GET_ROOM_PUSH_INFO,                 // ��ȡ����ʵʱ��Ϣ����
    SMSG_PLAYER_GET_ROOM_PUSH_INFO_RSP,             // ��ȡ����ʵʱ��Ϣ��Ӧ

    CMSG_PLAYER_GET_DICEROOM_TABLE_LIST = 5000, //����������б���T    SMSG_PLAYER_GET_DICEROOM_TABLE_LIST_RSP,    //����������б����    CMSG_PLAYER_REFRESH_DICEROOM_TABLES,        //ˢ�����������б�����
    SMSG_PLAYER_REFRESH_DICEROOM_TABLES_RSP,    //ˢ�����������б���Ӧ
    CMSG_PLAYER_CREATE_DICEROOM_TABLE,          //����������������
    SMSG_PLAYER_CREATE_DICEROOM_TABLE_RSP,      //��������������Ӧ
    
    SMSG_PLAYER_DICE_TABLE_INFO,                //������ͬ����������    SMSG_PLAYER_DICE_TABLE_INFO_SYNC,           //����������ͬ��������Ϣ
    SMSG_PLAYER_DICE_JOIN_TABLE_BROADCAST,      //����ҽ������ӹ��    CMSG_PLAYER_DICE_TABLE_READY,               //�������׼��
    SMSG_PLAYER_DICE_TABLE_READY_BROADCAST,     //���׼���㲥
    SMSG_PLAYER_DICE_TABLE_COUNTDOWN_BEGIN,     //��ʼ���ƕJ
    SMSG_PLAYER_DICE_TABLE_DEALER,                  //ׯ����Ϣ
    SMSG_PLAYER_DICE_TABLE_GAME_BEGIN_BROADCAST,    //��Ϸ����
    SMSG_PLAYER_DICE_ACTIVE_PLAYER,                 //��Ծ���
    SMSG_PLAYER_DICE_PLAYER_MIN_EFFICIENT_MONEY_IN_GAME,//��ǰ��Ϸ������ٽ�Ǯ��
    
    CMSG_PLAYER_DICE_TABLE_ANTE,                        //��ע����ע����ע���ӛ�    SMSG_PLAYER_DICE_TABLE_ANTE_RSP,                    //��ע��Ӧ
    SMSG_PLAYER_DICE_TABLE_ANTE_BROADCAST,              //��ע�㲥
    SMSG_PLAYER_DICE_TABLE_BASE_ANTE_BROADCAST,         //�µ�ע���    SMSG_PLAYER_DICE_TABLE_ANTE_TOTAL_COUNT_BROADCAST,  //�ܳ�����    CMSG_PLAYER_DICE_TABLE_LOOK_POKER,                  //������
    SMSG_PLAYER_DICE_TABLE_LOOK_POKER_RSP,              //������Ӧ
    SMSG_PLAYER_DICE_TABLE_LOOK_POKER_BROADCAST,        //��ҿ��ƹ㲥
    CMSG_PLAYER_DICE_TABLE_COMPARE,                     //�������
    SMSG_PLAYER_DICE_TABLE_COMPARE_RSP,                 //������Ӧ
    SMSG_PLAYER_DICE_TABLE_COMPARE_BROADCAST,           //��ұ��ƹ㲥
    CMSG_PLAYER_DICE_TABLE_FOLD,                        //��������
    SMSG_PLAYER_DICE_TABLE_FOLD_RSP,                    //������Ӧ
    SMSG_PLAYER_DICE_TABLE_FOLD_BROADCAST,              //������ƹ㲥

    SMSG_PLAYER_DICE_TABLE_ROUNDS_CHANGE,               //�����ִι㲥
    SMSG_PLAYER_DICE_TABLE_GAME_OVER_BROADCAST,         //��Ϸ����
    
    SMSG_PLAYER_DICE_PLAYER_EFFECTIVE_COINS_BROADCAST,  //��ҵ���Ч��Ǯ���Y    SMSG_PLAYER_DICE_PLAYER_HOUSE_MASTER_CHANGE,        //�����仯�㲥
    SMSG_PLAYER_DICE_TABLE_PLAYER_ONLINE_STATUS_CHANGED_BROADCAST,  //���״̬�仯���    CMSG_PLAYER_DICE_TABLE_FOLLOW_ALLTIME,              //��������Ƿ�һֱ������
    SMSG_PLAYER_DICE_TABLE_FOLLOW_ALLTIME_BROADCAST,    //�㲥����Ƿ������
    CMSG_PLAYER_SEND_SELECT_ABONDON_COLOR = 6000,       //����ѡȱ
    SMSG_PLAYER_SELECT_ABONDO_COLOR_BROADCAST,          //ѡȱ����㲥
    CMSG_PLAYER_SEND_CHANGE_MAHJONG_REQ,                //���ͻ�����T
    SMSG_PLAYER_SEND_CHANGE_MAHJONG_RSP,                //����������Ӧ
    SMSG_PLAYER_CHANGE_MAHJONG_FINISHED_BROADCAST,      //������ɹ㲥��Ϣ	
	SMSG_PLAYER_XUELIUCHENGHE_HU_BROADCAST,             // �Ĵ��齫Ѫ���ɺ���Һ��ƹ��    SMSG_PLAYER_XUELIUCHENGHE_POCHAN_BROADCAST,         // �Ĵ��齫Ѫ���ɺ�����Ʋ����    SMSG_PLAYER_XUELIUCHENGHE_POCHAN_RES,               // �Ĵ��齫Ѫ���ɺ�����Ʋ��؊B���䣬�䂞��Ԥ���Ӆ�    SMSG_PLAYER_XUELIUCHENGHE_GAMEOVER_BROADCAST,       // �Ĵ��齫Ѫ���ɺ���Ϸ�������    SMSG_PLAYER_XUELIUCHENGHE_OFFLINE_BROADCAST,        // �Ĵ��齫Ѫ���ɺӶ����������ӹ��    SMSG_PLAYER_XUELIUCHENGHE_POCHAN_BAOHU_RSP,         // �Ĵ��齫Ѫ���ɺ�����Ʋ���������    SMSG_PLAYER_XUELIUCHENGHE_POCHAN_BAOHU_BROADCAST,   // �Ĵ��齫Ѫ���ɺ�����Ʋ��������    SMSG_PLAYER_XUELIUCHENGHE_POCHAN_BAOHU_OVER,        // �Ĵ��齫Ѫ���ɺ�����Ʋ�������ֵ״̬�귿

    SMSG_PLAYER_1V1MJ_GAME_OVER = 6025,                 //�����齫��Ϸ����
    SMSG_PLAYER_1V1MJ_BUHUA_BROADCAST,                  //�����齫�����㲥
    SMSG_PLAYER_1V1MJ_BUHUA_RESP,                       //�����齫������Ӧ
    SMSG_PLAYER_1V1MJ_BUHUA_FINISH,                     //�����齫�������
    SMSG_PLAYER_1V1MJ_TASK_BROADCAST,                   //�����齫����㲥
    SMSG_PLAYER_1V1MJ_TASK_FINISH_RESP,                 //�����齫�������״̬resp
    SMSG_PLAYER_1V1MJ_OFFLINE_INFO,                     //�����齫��������
    SMSG_PUSH_ONE_USER_ATTR_INFO,                       //������ҵ���������-����
    SMSG_PUSH_MULTI_USER_ATTR_INFO,                     //������ҵ���������-�㲥
	CMSG_PLAYER_1V1MJ_TABLE_READY_REQ,					// �ͻ��˷������׼����T�����齫����׼��)
	SMSG_PLAYER_1V1MJ_MINGPAI_STATE_BROADCAST,			//�����齫���Ƴ��������״̬���	SMSG_PLAYER_1V1MJ_MINGPAI_USER_INFO_BROADCAST,		//�����齫���Ƴ����������Ϣ���	SMSG_PLAYER_1V1MJ_MINGPAI_USER_GET_MJ_BROADCAST,	//�����齫���Ƴ��������ȡ����Ϣ���	SMSG_PLAYER_1V1MJ_MINGPAI_CHATING_BROADCAST,		//�����齫���Ƴ�������Ϣ���	SMSG_PLAYER_1V1MJ_MINGPAI_BUHUA_INFO_BROADCAST,		//�����齫���Ƴ�������Ҳ������	SMSG_PLAYER_1V1MJ_MINGPAI_FINISH_INFO_BROADCAST,	//�����齫���Ƴ�������ɹ��
    CMSG_PLAYER_1V1MJ_SEND_SURRENDER,                   //�����齫����Ͷ�    SMSG_PLAYER_1V1MJ_SEND_SURRENDER_RESP,          //�����齫����Ͷ���؎�    SMSG_PLAYER_1V1MJ_RECV_SURRENDER,                   //�����齫�յ��Է�����Ͷ��
    CMSG_PLAYER_1V1MJ_ACK_SURRENDER,                  //�Ƿ�ͬ��Ͷ��
    SMSG_PLAYER_1V1MJ_ACK_SURRENDER_RESP,         //ͬ��Ͷ����Ӧ
    SMSG_PLAYER_1V1MJ_RECV_ACK_SURRENDER_RESP,         //ͬ��Ͷ���Է���Ӧ
    SMSG_PLAYER_1V1MJ_SURRENDER_GAME_OVER,    //Ͷ���ƾֽ����㲥
    CMSG_PLAYER_1V1MJ_SURRENDER_GET,                 //��ȡͶ����λ
    CMSG_PLAYER_1V1MJ_SURRENDER_GET_RESP,         //��ȡͶ����λ��Ӧ
    //��ս
    CMSG_PLAYER_ASK_IS_WATCHER = 6050,      //���ѯ���Ƿ�ΪΧ��Id
    SMSG_PLAYER_ASK_IS_WATCHER_RESP,        //������֪ͨ�Ƿ�ΪΧ��Id
    CMSG_PLAYER_REQUEST_WATCH_LIST,         //����Χ���б�
    SMSG_PLAYER_REQUEST_WATCH_LIST_RESP,    //����Χ���б�
    CMSG_PLAYER_ENTER_VIEW_TABLE,           //�ͻ������������ӄ    SMSG_PLAYER_ENTER_VIEW_TABLE_RESULT,    //�ͻ�����������Թ۽ᖨ    //Χ��������Э��    SMSG_PLAYER_ENTER_VIEWED_PLAYER_ID,    //���ӽ�Id
    SMSG_TABLE_WATCH_INFO,                 //����������Ƶ�����    SMSG_TABLE_WATCH_PLAYER_DEAL_MAHJONG,  //������һ����ҷ�һ������    CMSG_TABLE_WATCH_PLAYER_CHANGE_VIEW_PLAYER,   //Χ������л��ӽ�

    CMSG_COMP_GET_HALL_LIST = 7000,          //7000 ��������ȡ���d    SMSG_COMP_GET_HALL_LIST_RESP,            //7001 ��������ȡ�������    CMSG_COMP_GET_PLAYER_NUM,             //��ȡÿ���������˔�    SMSG_COMP_GET_PLAYER_NUM_RESP,
    CMSG_ENROLL_COMPETITION,                //����
    SMSG_ENROLL_COMPETITION_RESP,
    SMSG_COMP_COMPETITION_WILL_BEGIN_RSP,//��ʾ��ң�������������    SMSG_COMP_PRIZE_RSP, // ��������
    SMSG_COMP_WAIT_OTHER_TABLE,//�����ж�����δ����
    SMSG_COMP_WAIT_OTHER_TABLE_RESP, //��ʾ��ң����м���δ���������Ņ�    CMSG_EXIT_COMPETITION,//���d    SMSG_EXIT_COMPETITION_RESP,
    CMSG_NEED_SYNC_NUMS,//��������] ��Ҫͬ���˔�    SMSG_NEED_SYNC_NUMS_RSP,//��������] ��Ҫͬ���˔�    CMSG_CANCEL_SYNC_NUMS,//����˳�������  ȡ��ͬ��
    SMSG_CANCEL_SYNC_NUMS_RSP,
    CMSG_GET_COMPETITION_CHART,//��ȡ�������И�    SMSG_GET_COMPETITION_CHART_RESP,
    CMSG_GET_COMPETITION_GET_PLAYER_INFO,//��ȡ��ұ�������
    SMSG_GET_COMPETITION_GET_PLAYER_INFO_RESP,

	// Gateway Message (ר��)
	GATEWAY_MSG = 9001,
	GATEWAY_MSG_RESP,
	GATEWAY_SESSION_MSG_RESP,

	GMSG_CLIENT_LOGOUT,		// �ͻ����˳���GameServer(����Gateway Server)
	SMSG_CLIENT_LOGOUT_RESP,

	GMSG_CLIENT_OFFLINE, //�ͻ��˶���	
	GMSG_AVATAR_UPDATE, //avatarͷ�����

	// �ͻ��˽���ר�m	UIMSG_POPUP_BUTTON_CLICKED = 10001,
	UIMSG_CANCEL_LOADING,

	CSMSG_COUNT,
};
#endif  // MUDUO_EXAMPLES_BAINAGAME_OP_CODEC_H
