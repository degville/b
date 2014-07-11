/*

	nw2s::b - A microcontroller-based modular synth control framework
	Copyright (C) 2013 Scott Wilson (thomas.scott.wilson@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef SignalData_h
#define SignalData_h

#include <SD.h>

namespace nw2s
{		
	class SignalData;
	class StreamingSignalData;

	static const int STREAM_BUFFER_SIZE = 4096;
	static const int READ_BUFFER_SIZE = STREAM_BUFFER_SIZE * 2;

	static const unsigned int SIGNAL_SAW[600] = 
	{
		200000,
		200665,
		201331,
		202002,
		202667,
		203333,
		203998,
		204669,
		205334,
		206000,
		206665,
		207330,
		208002,
		208667,
		209332,
		209998,
		210669,
		211334,
		212000,
		212665,
		213330,
		214001,
		214667,
		215332,
		215997,
		216669,
		217334,
		217999,
		218665,
		219330,
		220001,
		220667,
		221332,
		221997,
		222668,
		223334,
		223999,
		224664,
		225330,
		226001,
		226666,
		227332,
		227997,
		228668,
		229333,
		229999,
		230664,
		231329,
		232001,
		232666,
		233331,
		233997,
		234668,
		235333,
		235999,
		236664,
		237335,
		238000,
		238666,
		239331,
		239996,
		240668,
		241333,
		241998,
		242664,
		243335,
		244000,
		244666,
		245331,
		245996,
		246667,
		247333,
		247998,
		248663,
		249335,
		250000,
		250665,
		251331,
		251996,
		252667,
		253333,
		253998,
		254663,
		255334,
		256000,
		256665,
		257330,
		257996,
		258667,
		259332,
		259998,
		260663,
		261334,
		262000,
		262665,
		263330,
		263995,
		264667,
		265332,
		265997,
		266663,
		267334,
		267999,
		268665,
		269330,
		269995,
		270667,
		271332,
		271997,
		272662,
		273334,
		273999,
		274664,
		275330,
		275995,
		276666,
		277332,
		277997,
		278662,
		279333,
		279999,
		280664,
		281329,
		281995,
		282666,
		283331,
		283997,
		284662,
		285333,
		285999,
		286664,
		287329,
		287994,
		288666,
		289331,
		289996,
		290662,
		291333,
		291998,
		292664,
		293329,
		293994,
		294666,
		295331,
		295996,
		296661,
		297333,
		297998,
		298663,
		299329,
		299994,
		300665,
		301331,
		301996,
		302661,
		303333,
		303998,
		304663,
		305328,
		306000,
		306665,
		307330,
		307996,
		308661,
		309332,
		309998,
		310663,
		311328,
		312000,
		312665,
		313330,
		313995,
		314661,
		315332,
		315997,
		316663,
		317328,
		317999,
		318665,
		319330,
		319995,
		320660,
		321332,
		321997,
		322662,
		323328,
		323999,
		324664,
		325330,
		325995,
		326660,
		327332,
		327997,
		328662,
		329327,
		329999,
		330664,
		331329,
		331995,
		332660,
		333331,
		333997,
		334662,
		335327,
		335999,
		336664,
		337329,
		337994,
		338660,
		339331,
		339996,
		340662,
		341327,
		341998,
		342664,
		343329,
		343994,
		344659,
		345331,
		345996,
		346661,
		347327,
		347998,
		348663,
		349329,
		349994,
		350659,
		351331,
		351996,
		352661,
		353326,
		353998,
		354663,
		355328,
		355994,
		356659,
		357330,
		357996,
		358661,
		359326,
		359998,
		360663,
		361328,
		361993,
		362659,
		363330,
		363995,
		364661,
		365326,
		365997,
		366663,
		367328,
		367993,
		368665,
		369330,
		369995,
		370660,
		371326,
		371997,
		372662,
		373328,
		373993,
		374664,
		375330,
		375995,
		376660,
		377325,
		377997,
		378662,
		379327,
		379993,
		380664,
		381329,
		381995,
		382660,
		383325,
		383997,
		384662,
		385327,
		385992,
		386664,
		387329,
		387994,
		388660,
		389325,
		389996,
		390662,
		391327,
		391992,
		392664,
		393329,
		393994,
		394659,
		395325,
		395996,
		396661,
		397327,
		397992,
		398663,
		399329,
		6,
		671,
		1337,
		2008,
		2673,
		3339,
		4004,
		4675,
		5341,
		6006,
		6671,
		7336,
		8008,
		8673,
		9338,
		10004,
		10675,
		11340,
		12006,
		12671,
		13336,
		14008,
		14673,
		15338,
		16003,
		16675,
		17340,
		18005,
		18671,
		19336,
		20007,
		20673,
		21338,
		22003,
		22675,
		23340,
		24005,
		24670,
		25336,
		26007,
		26672,
		27338,
		28003,
		28674,
		29340,
		30005,
		30670,
		31335,
		32007,
		32672,
		33337,
		34003,
		34674,
		35339,
		36005,
		36670,
		37341,
		38007,
		38672,
		39337,
		40002,
		40674,
		41339,
		42004,
		42670,
		43341,
		44006,
		44672,
		45337,
		46002,
		46674,
		47339,
		48004,
		48669,
		49341,
		50006,
		50671,
		51337,
		52002,
		52673,
		53339,
		54004,
		54669,
		55341,
		56006,
		56671,
		57336,
		58002,
		58673,
		59338,
		60004,
		60669,
		61340,
		62006,
		62671,
		63336,
		64001,
		64673,
		65338,
		66003,
		66669,
		67340,
		68005,
		68671,
		69336,
		70001,
		70673,
		71338,
		72003,
		72668,
		73340,
		74005,
		74670,
		75336,
		76001,
		76672,
		77338,
		78003,
		78668,
		79340,
		80005,
		80670,
		81335,
		82001,
		82672,
		83337,
		84003,
		84668,
		85339,
		86005,
		86670,
		87335,
		88000,
		88672,
		89337,
		90002,
		90668,
		91339,
		92004,
		92670,
		93335,
		94000,
		94672,
		95337,
		96002,
		96667,
		97339,
		98004,
		98669,
		99335,
		100006,
		100671,
		101337,
		102002,
		102667,
		103339,
		104004,
		104669,
		105334,
		106006,
		106671,
		107336,
		108002,
		108667,
		109338,
		110004,
		110669,
		111334,
		112006,
		112671,
		113336,
		114001,
		114667,
		115338,
		116003,
		116669,
		117334,
		118005,
		118671,
		119336,
		120001,
		120667,
		121338,
		122003,
		122668,
		123334,
		124005,
		124670,
		125336,
		126001,
		126666,
		127338,
		128003,
		128668,
		129333,
		130005,
		130670,
		131335,
		132001,
		132666,
		133337,
		134003,
		134668,
		135333,
		136005,
		136670,
		137335,
		138000,
		138666,
		139337,
		140002,
		140668,
		141333,
		142004,
		142670,
		143335,
		144000,
		144666,
		145337,
		146002,
		146667,
		147333,
		148004,
		148669,
		149335,
		150000,
		150665,
		151337,
		152002,
		152667,
		153333,
		154004,
		154669,
		155334,
		156000,
		156665,
		157336,
		158002,
		158667,
		159332,
		160004,
		160669,
		161334,
		162000,
		162665,
		163336,
		164001,
		164667,
		165332,
		166003,
		166669,
		167334,
		167999,
		168671,
		169336,
		170001,
		170667,
		171332,
		172003,
		172668,
		173334,
		173999,
		174670,
		175336,
		176001,
		176666,
		177332,
		178003,
		178668,
		179333,
		179999,
		180670,
		181335,
		182001,
		182666,
		183331,
		184003,
		184668,
		185333,
		185999,
		186670,
		187335,
		188000,
		188666,
		189331,
		190002,
		190668,
		191333,
		191998,
		192670,
		193335,
		194000,
		194666,
		195331,
		196002,
		196667,
		197333,
		197998,
		198669,
		199335
	};

	static const unsigned int SIGNAL_VOX[600] = 
	{
		205078,
		211792,
		211523,
		207190,
		202563,
		202759,
		209985,
		222559,
		235620,
		242651,
		242749,
		238745,
		234937,
		233911,
		239575,
		253015,
		269360,
		281775,
		286084,
		285046,
		282751,
		282214,
		285693,
		294202,
		305878,
		314032,
		313837,
		304791,
		293591,
		287146,
		288281,
		295117,
		305292,
		315363,
		320953,
		320941,
		320331,
		324408,
		332709,
		342169,
		351752,
		359283,
		363019,
		362640,
		360077,
		357367,
		355939,
		357880,
		364642,
		373492,
		378583,
		377740,
		376031,
		378253,
		383099,
		387079,
		391437,
		398370,
		399994,
		393195,
		378375,
		366583,
		361371,
		360883,
		362726,
		365033,
		364886,
		362897,
		362408,
		363409,
		363849,
		364996,
		371552,
		384552,
		395197,
		396552,
		389557,
		381146,
		374969,
		370428,
		366730,
		365094,
		367352,
		371417,
		370953,
		362225,
		346954,
		333344,
		326715,
		327411,
		330402,
		330609,
		326093,
		317926,
		308026,
		298608,
		291479,
		289453,
		293945,
		304059,
		313422,
		317853,
		318207,
		317352,
		317194,
		319476,
		325116,
		332538,
		337677,
		338153,
		333844,
		324835,
		312213,
		301190,
		295203,
		294116,
		293713,
		290100,
		283936,
		279346,
		277222,
		276013,
		274585,
		273743,
		274622,
		277490,
		280981,
		282678,
		281055,
		278723,
		279517,
		284460,
		290295,
		294568,
		297620,
		300116,
		300238,
		297266,
		293152,
		290918,
		290735,
		290320,
		287390,
		281799,
		274609,
		267566,
		260974,
		255273,
		250867,
		248303,
		246875,
		245190,
		242224,
		238623,
		236853,
		238306,
		241138,
		242712,
		241956,
		239758,
		236572,
		231616,
		226245,
		223096,
		223596,
		225977,
		227332,
		226270,
		223645,
		220557,
		217310,
		213904,
		210681,
		207251,
		202747,
		196716,
		188770,
		179517,
		171716,
		166223,
		161926,
		157849,
		153882,
		150452,
		147107,
		143298,
		139111,
		135559,
		133594,
		132910,
		132922,
		133057,
		132617,
		130737,
		127271,
		123132,
		119934,
		117993,
		116382,
		114294,
		111914,
		109558,
		106335,
		101147,
		94977,
		89349,
		85162,
		82025,
		78143,
		72589,
		65753,
		59857,
		55792,
		53192,
		51703,
		51630,
		53595,
		56525,
		58392,
		58087,
		56854,
		56781,
		58173,
		59589,
		59979,
		59418,
		58002,
		55963,
		53717,
		52020,
		51520,
		51874,
		52448,
		52484,
		51727,
		50409,
		48883,
		47577,
		46661,
		46405,
		46796,
		47174,
		47040,
		46564,
		46149,
		46063,
		46625,
		48334,
		51569,
		56183,
		60834,
		64618,
		67474,
		69904,
		72699,
		75824,
		78473,
		80707,
		83087,
		85480,
		87408,
		88434,
		88654,
		88898,
		90082,
		92535,
		95160,
		96967,
		97845,
		98322,
		98700,
		98907,
		99066,
		99725,
		101074,
		102771,
		104419,
		106250,
		108728,
		111755,
		115247,
		119299,
		123596,
		127832,
		131580,
		134399,
		136438,
		137878,
		139026,
		139844,
		140100,
		139685,
		138904,
		137866,
		136584,
		135400,
		134644,
		134351,
		134180,
		133960,
		133948,
		134302,
		134790,
		135193,
		135571,
		136121,
		136890,
		137659,
		138171,
		138647,
		139294,
		140234,
		141284,
		142285,
		143030,
		143555,
		144226,
		145117,
		145618,
		145227,
		143909,
		142114,
		140198,
		138464,
		136938,
		135608,
		134204,
		132617,
		131213,
		130286,
		129932,
		129993,
		130225,
		130518,
		130774,
		130823,
		130396,
		129602,
		129102,
		129187,
		129712,
		130151,
		130249,
		130139,
		130225,
		130725,
		131665,
		132703,
		133618,
		134351,
		134924,
		135156,
		134949,
		134558,
		134351,
		134290,
		134180,
		133862,
		133228,
		132373,
		131738,
		131555,
		131897,
		132922,
		134473,
		136353,
		138428,
		140356,
		142029,
		143591,
		145398,
		147803,
		151001,
		154907,
		159680,
		165198,
		171619,
		178271,
		184229,
		187695,
		188464,
		188867,
		190063,
		191187,
		191479,
		191284,
		190710,
		188647,
		184729,
		180176,
		177441,
		178271,
		183472,
		190967,
		197754,
		201794,
		203076,
		203223,
		203821,
		206165,
		211096,
		218506,
		226953,
		232678,
		233789,
		231348,
		229199,
		229797,
		233752,
		239612,
		245850,
		250781,
		252856,
		250854,
		245654,
		240259,
		238330,
		240369,
		244629,
		247632,
		247522,
		244507,
		240857,
		238220,
		237439,
		239368,
		244031,
		249927,
		254358,
		255127,
		253113,
		250342,
		248755,
		248608,
		249390,
		250330,
		250745,
		249866,
		247241,
		244104,
		242285,
		242627,
		244250,
		245618,
		245642,
		244141,
		241650,
		238770,
		236169,
		233472,
		230249,
		226440,
		222571,
		218494,
		214111,
		210352,
		207898,
		206824,
		206641,
		206482,
		205872,
		205042,
		204443,
		204272,
		204504,
		205115,
		205713,
		205945,
		206116,
		206555,
		207166,
		207764,
		208618,
		209888,
		211035,
		211353,
		210400,
		207947,
		204126,
		199036,
		192896,
		186804,
		181116,
		176074,
		172070,
		168652,
		165588,
		163513,
		162927,
		164001,
		166333,
		169055,
		172241,
		176245,
		180115,
		182532,
		182568,
		180750,
		178601,
		177087,
		176135,
		175000,
		173572,
		172046,
		170361,
		167969,
		164917,
		162708,
		162463,
		163940,
		165356,
		165308,
		163452,
		160889,
		158691,
		157471,
		157520,
		159204,
		162244,
		165356,
		166797,
		166516,
		165698,
		165796,
		167224,
		169531,
		171680,
		172949,
		172913,
		171436,
		168811,
		165735,
		163660,
		164429,
		167944,
		171973,
		173743,
		173535,
		172644,
		172107,
		172522,
		173938,
		175757,
		176807,
		176770,
		175269,
		172119,
		168188,
		165320,
		165100,
		167004,
		169690,
		172571,
		175867,
		179858,
		183984,
		187366,
		190271,
		192847,
		194238,
		193616,
		190649,
		186377,
		181860,
		178381,
		176538,
		175854,
		174866,
		172681,
		170251,
		168909,
		169336,
		171814,
		176880,
		184546,
		192383,
		197913,
		199341,
		197156,
		194690,
		194995,
		198523,
		202917,
		206055,
		206604,
		204089,
		198987,
		192712,
		188220,
		187024,
		189734,
		195801,
		202112,
		205371,
		203613,
		198755,
		194495,
		193250,
		196313,
		199329		
	};


}

class nw2s::SignalData
{
	public:
		static SignalData* fromArray(unsigned short int* source, long size);
		static SignalData* fromSDFile(char *filepath);
		long getSize();
		short unsigned int getSample(long sample);
	
	private:
		short unsigned int *data;
		int size;
		static bool initialized;
		
		SignalData(short unsigned int *data, long size);
		
};

class nw2s::StreamingSignalData
{
	public:
		static StreamingSignalData* fromSDFile(char *foldername, char* subfoldername, char *filename, bool loop = false);
		short unsigned int getNextSample();
		bool isAvailable();
		bool isReadyForRefresh();
		void refresh();
		void reset();
		
	private:
		short unsigned int buffer[2][nw2s::STREAM_BUFFER_SIZE];
		short volatile unsigned int readbufferindex;
		short volatile unsigned int writebufferindex;
		int size[2];
		volatile int nextsampleindex;
		bool available;
		bool loop;
		SdFile file;
		
		StreamingSignalData(char *foldername, char* subfoldername, char *filename, bool loop = false);
};

#endif

