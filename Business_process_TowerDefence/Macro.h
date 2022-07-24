#include "Business_process_2.h"
//#include "StoneDefenceUtils.h"


#define Macro_print_s(Format,...) \
{const FString Msg_s = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg_s);}

#define Macro_print(Type,Format,...) \
{const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(LogStoneDefence,Type,TEXT("%s"),*Msg);}


#if WITH_EDITOR																	//�ڱ�����������: ��ӡ����Ļ
#define Macro_print_r(Type,Format,...) \
{const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg); \
UE_LOG(LogStoneDefence,Type,TEXT("%s"),*Msg);}			//��������, ��Ϣ, 
#else																			//�Ǳ�����: 
#define Macro_print_r(Type,Format,...) \
Macro_print(Type,Format, ##__VA_ARGS__)
#endif



