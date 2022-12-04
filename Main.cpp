# include <Siv3D.hpp> // OpenSiv3D v0.6.5

#define Zihou_VOLUME 0.5


bool announce(DateTime TIME) {
	String s = {};
	if (TIME.hour == 11 && TIME.minute == 59 && TIME.second >= 50) {
		Say << U"正午をお知らせします。";
		return 0;
	}
	if (TIME.minute==59&&TIME.second>=50)
	{
		if (TIME.hour >= 12&&TIME.hour<=22)s += U"午後 ";
		else s += U"午前 ";
		s += Format((TIME.hour + 1) % 24);
		s += U"時 ちょうどを お知らせします。";
		Say << s;
		return 0;
	}
	if (TIME.hour >= 12)s += U"午後 ";
	else s += U"午前 ";
	s += Format(TIME.hour);
	s += U"時 ";
	if (TIME.second >= 50) {
		s += Format(TIME.minute + 1);
		s += U"分 ちょうどを お知らせします。";
		Say << s;
		return 0;
	}
	if (TIME.minute != 0) {
		s += Format(TIME.minute);
		s += U"分 ";
	}
	s += Format((TIME.second / 10 + 1) * 10);
	s += U"秒を お知らせします。";
	Say << s;
	return 0;
}

void Main()
{
	auto nowtime = DateTime::Now();//現在時刻を格納
	const Font ddegi{50,U"../App/Fonts/DSEG7Classic.ttf"};//日付オブジェクトを設定
	const Font degi{150,U"../App/Fonts/DSEG7Classic.ttf" };//時計オブジェクトを設定
	const Font mdegi{50,U"../App/Fonts/DSEG7Classic.ttf" };//デシ秒オブジェクトを設定
	auto lastsay = nowtime;//最終読み上げ時刻を格納

	TextToSpeech::SetDefaultLanguage(LanguageCode::Japanese);//Sayを設定
	TextToSpeech::SetVolume(1);
	TextToSpeech::SetSpeed(0.8);

	const Audio sinelow { U"../App/Tone/500hz.wav" };
	const Audio sinemid { U"../App/Tone/1000hz.wav" };
	const Audio sinehigh{ U"../App/Tone/2000hz.wav" };

	bool secondmute = 0;

	for (const auto& path : EnumResourceFiles()){
		Console << path;
	}


	while (System::Update())//本文
	{
		nowtime = DateTime::Now();//現在時刻を更新
		ddegi(nowtime.format(U"yyyy-MM-dd")).drawAt(380,60);//時計オブジェクトを設置＆更新
		degi(nowtime.format(U"HH:mm:ss")).drawAt(380, 200);//時計オブジェクトを設置＆更新
		mdegi(nowtime.format(U"SS")).draw(700, 300);//時計オブジェクトを設置＆更新

		//Console << Format(nowtime.second % 30 - 27);//デバッグコンソールに最終読み上げ時刻を出力
		if (nowtime.second != lastsay.second) {
			lastsay = nowtime;//最終読み上げ時刻を更新

			if (nowtime.second % 10 == 0) {
				sinemid.playOneShot(Zihou_VOLUME);
				announce(nowtime);
			}
			else if ((nowtime.second % 30 - 27) >= 0) {sinelow.playOneShot(Zihou_VOLUME);}
			sinehigh.playOneShot(secondmute ? 0 : Zihou_VOLUME);
		}
		SimpleGUI::CheckBox(secondmute, U"毎秒の時報音をミュート", { 0, 500 }, 270, true);
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
