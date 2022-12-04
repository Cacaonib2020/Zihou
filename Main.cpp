# include <Siv3D.hpp> // OpenSiv3D v0.6.5


String ms(auto m) {
	m /= 10;
	String r = {};
	//if (m < 100)r += '0';
	if (m < 10)r += '0';
	r += Format(m);
	return r;
}

void Main()
{
	auto nowtime = DateTime::Now();//現在時刻を格納
	const Font degi{50};//時計オブジェクトを設定
	const Font mdegi{25};//時計オブジェクトを設定
	auto lastsay = nowtime;//最終読み上げ時刻を格納
	TextToSpeech::SetDefaultLanguage(LanguageCode::Japanese);//Sayする言語を設定

	const Audio sinelow { U"C:/Users/yuzu6/WorkSpace/PlayGround/C++/Zihou/Tone/500hz.wav"};
	const Audio sinemid { U"C:/Users/yuzu6/WorkSpace/PlayGround/C++/Zihou/Tone/1000hz.wav" };
	const Audio sinehigh{ U"C:/Users/yuzu6/WorkSpace/PlayGround/C++/Zihou/Tone/2000hz.wav"};

	Say << Format(nowtime).substr(11,12);//現在時刻を読み上げ
	while (TextToSpeech::IsSpeaking());//読み上げ終了まで待機
	while (System::Update())//本文
	{
		nowtime = DateTime::Now();//現在時刻を更新
		degi(nowtime).draw(20, 20);//時計オブジェクトを設置＆更新
		mdegi(ms(nowtime.milliseconds)).draw(550, 50);//時計オブジェクトを設置＆更新

		//Console << Format(nowtime.second % 30 - 27);//デバッグコンソールに最終読み上げ時刻を出力
		if (nowtime.second != lastsay.second) {
			lastsay = nowtime;//最終読み上げ時刻を更新

			if (nowtime.second % 10 == 0) {sinemid.playOneShot();}
			else if ((nowtime.second % 30 - 27) >= 0) {sinelow.playOneShot();}
			sinehigh.playOneShot();
		}
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
