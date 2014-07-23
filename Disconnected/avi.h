#ifndef _AVI_H
#define _AVI_H

typedef unsigned char	byte;	/* 8-bit */
typedef unsigned short	word;	/* 16-bit */
typedef unsigned int	dword;	/* 32-bit */

#define FRAME_BUFFER_MAX 10
#define FRAME_BUFFER_SIZE 1024*60

typedef struct _avi_avih {
	byte fcc[4];   // ����Ϊ��avih��
	dword  cb;    // �����ݽṹ�Ĵ�С�������������8���ֽڣ�fcc��cb������
	dword  dwMicroSecPerFrame;   // ��Ƶ֡���ʱ�䣨�Ժ���Ϊ��λ��
	dword  dwMaxBytesPerSec;     // ���AVI�ļ������������
	dword  dwPaddingGranularity; // ������������
	dword  dwFlags;         // AVI�ļ���ȫ�ֱ�ǣ������Ƿ����������
	dword  dwTotalFrames;   // ��֡��
	dword  dwInitialFrames; // Ϊ������ʽָ����ʼ֡�����ǽ�����ʽӦ��ָ��Ϊ0��
	dword  dwStreams;       // ���ļ����������ĸ���
	dword  dwSuggestedBufferSize; // �����ȡ���ļ��Ļ����С��Ӧ���������Ŀ飩
	dword  dwWidth;         // ��Ƶͼ��Ŀ�������Ϊ��λ��
	dword  dwHeight;        // ��Ƶͼ��ĸߣ�������Ϊ��λ��
	dword  dwReserved[4];   // ����
} AVI_AVIH;

typedef struct _avi_strh {
	byte fcc[4];  // ����Ϊ��strh��
	dword  cb;   // �����ݽṹ�Ĵ�С�������������8���ֽڣ�fcc��cb������
	byte fccType[4];    // �������ͣ���auds������Ƶ��������vids������Ƶ������
	              //��mids����MIDI��������txts������������
	byte fccHandler[4]; // ָ�����Ĵ����ߣ���������Ƶ��˵���ǽ�����
	dword  dwFlags;    // ��ǣ��Ƿ�����������������ɫ���Ƿ�仯��
	word   wPriority;  // �������ȼ������ж����ͬ���͵���ʱ���ȼ���ߵ�ΪĬ������
	word   wLanguage;
	dword  dwInitialFrames; // Ϊ������ʽָ����ʼ֡��
	dword  dwScale;   // �����ʹ�õ�ʱ��߶�
	dword  dwRate;
	dword  dwStart;   // ���Ŀ�ʼʱ��
	dword  dwLength;  // ���ĳ��ȣ���λ��dwScale��dwRate�Ķ����йأ�
	dword  dwSuggestedBufferSize; // ��ȡ��������ݽ���ʹ�õĻ����С
	dword  dwQuality;    // �����ݵ�����ָ�꣨0 ~ 10,000��
	dword  dwSampleSize; // Sample�Ĵ�С
	struct {
		short int left;
		short int top;
		short int right;
		short int bottom;
	} rcFrame;  // ָ�����������Ƶ����������������Ƶ�������е���ʾλ��
             // ��Ƶ��������AVIMAINHEADER�ṹ�е�dwWidth��dwHeight����
} AVI_STRH;

#pragma pack(2)
typedef struct _TBitmapInfoHeader {
	byte        fcc[4];     //'strf'
	dword       cb;
	dword       biSize;
	dword       biWidth;
	dword       biHeight;
	word        biPlanes;
	word        biBitCount;
	byte        biCompression[4];
	dword       biSizeImage;
	dword       biXPelsPerMeter;
	dword       biYPelsPerMeter;
	dword       biClrUsed;
	dword       biClrImportant;
}TBitmapInfoHeader;
#pragma option pop

#pragma pack(2)
typedef struct _TWaveFormatEx {
	byte        fcc[4];     //'strf'
	dword       cb;
	word        wFormatTag;         // format type
	word        nChannels;          // number of channels (i.e. mono, stereo...) 
	dword       nSamplesPerSec;     // sample rate 
	dword       nAvgBytesPerSec;    // for buffer estimation 
	word        nBlockAlign;        // block size of data 
	word        wBitsPerSample;     // number of bits per sample of mono data 
	dword        cbSize;             // the count in bytes of the size of 
} TWaveFormatEx;
#pragma option pop

typedef struct _avi_strl_video {
	byte               fcc_strl[4];      //����Ϊ'strl'
	AVI_STRH           avi_stream;
	TBitmapInfoHeader  stream_format;
} AVI_STRL_VIDEO;

typedef struct _avi_strl_audio {
	byte           fcc_strl[4];      //����Ϊ'strl'
	AVI_STRH       avi_stream;
	TWaveFormatEx  stream_format;
} AVI_STRL_AUDIO;



typedef struct _avi_header {
	byte   fcc[4];    //����Ϊ'RIFF'
	dword  dwavisize;    //avi���ݴ�С
	byte   filetype[4];   //�ļ�����
	
	byte            fcc_list_p[4];    //'LIST'
	dword           list_p_size;      // 4 + sizeof(AVI_AVIH) + 4 + 4 + sizeof(AVI_STRL_VIDEO) + sizeof(AVI_STRL_audio)
	byte            fcc_hdrl[4];      //'hdrl'
	AVI_AVIH        mainheader;
	
	byte            fcc_list_v[4];    //'LIST'
	dword           list_v_size;      // sizeof(AVI_STRL_VIDEO)
	AVI_STRL_VIDEO  video_info;
//	byte            fcc_list_a[4];    //'LIST'
//	dword           list_a_size;      // sizeof(AVI_STRL_AUDIO)
//	AVI_STRL_AUDIO  audio_info;
	
	byte            fcc_list_m[4];    //'LIST'
	dword           list_m_size;
	byte            fcc_movi[4];      //'movi'
} AVI_HEADER;

typedef struct _avioldindex_entry {
	dword   dwChunkId;   // ���������ݿ�����ַ���
	dword   dwFlags;     // ˵�������ݿ��ǲ��ǹؼ�֡���ǲ��ǡ�rec ���б����Ϣ
	dword   dwOffset;    // �����ݿ����ļ��е�ƫ����
	dword   dwSize;      // �����ݿ�Ĵ�С
} AVI_INDEX;

typedef struct _frame_block {
	byte fcc[4];
	dword size;
	unsigned char fb[FRAME_BUFFER_SIZE];
} FRAME_BLOCK;

typedef struct _frame_buffer {
	sem_t *sem_lock;
	FRAME_BLOCK blk;
} FRAME_BUFFER;

typedef struct _video_config {
	char filename[512];
	unsigned int width;
	unsigned int height;
	unsigned int framerate;
	unsigned int gop;
//	dword IFrameInterval;
	unsigned int write_frame_count;
	FILE *fd;
	size_t frame_max_size;
	void *(*start_routine)(void *);
} AVI_CONFIG;

typedef struct video_profile
{
    unsigned int bit_rate;
    unsigned int width;   //length per dma buffer
    unsigned int height;
    unsigned int framerate;
    unsigned int frame_rate_base;
    unsigned int gop_size;
    unsigned int qmax;
    unsigned int qmin;   
    unsigned int quant;
//++ Foster
//    unsigned int enable_4mv;
//-- Foster
    void *coded_frame;
}video_profile;

#endif
