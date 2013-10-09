#include "DxLib.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode( TRUE );
	SetUseBackBufferTransColorFlag( TRUE );
	if ( DxLib_Init( ) == -1 ) return -1;

	int gh = LoadGraph( "AlphaCircle.png" );
	int sh = LoadSoftImage( "AlphaCircle.png" );

	SetDrawValidAlphaChannelGraphCreateFlag( TRUE );
	int bgh = MakeScreen( 256, 256 );	// α付のバッファを作成
	SetDrawValidAlphaChannelGraphCreateFlag( FALSE );

	int bsh = MakeARGB8ColorSoftImage( 640, 480 );
	int csh = MakeARGB8ColorSoftImage( 256, 256 );

	SetTransColor( 0, 255, 0 );

	SetDrawScreen( bgh );
	FillGraph( bgh, 0, 0, 0, 0 );

	// BlendParam と画像のα値が乗算されますので、255を指定すれば
	// 画像のα値がそのまま描画先に書き込まれます
	SetDrawBlendMode( DX_BLENDMODE_SRCCOLOR, 255 ) ;

	DrawGraph( 0, 0, gh, TRUE );	// α付のバッファにレンダリング

	// ブレンドモードを元に戻す
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 ) ;

	GetDrawScreenSoftImage( 0, 0, 256, 256, csh );	// レンダリング結果をソフトイメージに取得

	FillSoftImage( bsh, 0, 0, 0, 0 ) ;
	BltSoftImage( 0, 0, 256, 256,  sh, 0,   0, bsh );	// ソフトイメージに読み込んだ画像を直接出力
	BltSoftImage( 0, 0, 256, 256, csh, 0, 240, bsh );	// バッファを使って加工した画像を出力

	UpdateLayerdWindowForSoftImage( bsh );

	WaitKey( );
	DxLib_End( ); 
	return 0;
}