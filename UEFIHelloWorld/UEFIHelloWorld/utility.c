
// https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170#x64-register-usage

 void __fastcall delay(long delayCount)
{
	 while (delayCount--);
}