#include "Business_process_2.h"
//#include "StoneDefenceUtils.h"


#define Macro_print_s(Format,...) \
{const FString Msg_s = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg_s);}

#define Macro_print(Type,Format,...) \
{const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(LogStoneDefence,Type,TEXT("%s"),*Msg);}


#if WITH_EDITOR																	//在编译器中运行: 打印在屏幕
#define Macro_print_r(Type,Format,...) \
{const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg); \
UE_LOG(LogStoneDefence,Type,TEXT("%s"),*Msg);}			//断言类型, 信息, 
#else																			//非编译器: 
#define Macro_print_r(Type,Format,...) \
Macro_print(Type,Format, ##__VA_ARGS__)
#endif



