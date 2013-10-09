#include "DxLib.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode( TRUE );
	SetUseBackBufferTransColorFlag( TRUE );
	if ( DxLib_Init( ) == -1 ) return -1;

	int gh = LoadGraph( "AlphaCircle.png" );
	int sh = LoadSoftImage( "AlphaCircle.png" );

	SetDrawValidAlphaChannelGraphCreateFlag( TRUE );
	int bgh = MakeScreen( 256, 256 );	// ���t�̃o�b�t�@���쐬
	SetDrawValidAlphaChannelGraphCreateFlag( FALSE );

	int bsh = MakeARGB8ColorSoftImage( 640, 480 );
	int csh = MakeARGB8ColorSoftImage( 256, 256 );

	SetTransColor( 0, 255, 0 );

	SetDrawScreen( bgh );
	FillGraph( bgh, 0, 0, 0, 0 );

	// BlendParam �Ɖ摜�̃��l����Z����܂��̂ŁA255���w�肷���
	// �摜�̃��l�����̂܂ܕ`���ɏ������܂�܂�
	SetDrawBlendMode( DX_BLENDMODE_SRCCOLOR, 255 ) ;

	DrawGraph( 0, 0, gh, TRUE );	// ���t�̃o�b�t�@�Ƀ����_�����O

	// �u�����h���[�h�����ɖ߂�
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 ) ;

	GetDrawScreenSoftImage( 0, 0, 256, 256, csh );	// �����_�����O���ʂ��\�t�g�C���[�W�Ɏ擾

	FillSoftImage( bsh, 0, 0, 0, 0 ) ;
	BltSoftImage( 0, 0, 256, 256,  sh, 0,   0, bsh );	// �\�t�g�C���[�W�ɓǂݍ��񂾉摜�𒼐ڏo��
	BltSoftImage( 0, 0, 256, 256, csh, 0, 240, bsh );	// �o�b�t�@���g���ĉ��H�����摜���o��

	UpdateLayerdWindowForSoftImage( bsh );

	WaitKey( );
	DxLib_End( ); 
	return 0;
}