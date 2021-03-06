#include "DeSerializer.h"

struct Data1 {
	uint64_t a;
	bool b;
	uint64_t c;
	template <class Serializer> Error serialize(Serializer& serializer) {
		return serializer(a, b, c);
	}
};

struct Data2 {
	uint64_t a;
	template <class Serializer> Error serialize(Serializer& serializer) {
		return serializer(a);
	}
};

struct Data3 {
	bool a;
	template <class Serializer> Error serialize(Serializer& serializer) {
		return serializer(a);
	}
};

void DefaultTest() {
	Data1 x { 1, true, 2 };
	std::stringstream stream;
	Serializer serializer(stream);
	Error errx = serializer.save(x);
	assert(errx == Error::NoError);
	assert(stream.str() == "1 true 2 ");

	Data1 y { 0, false, 0 };
	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);
	assert(err == Error::NoError);
	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
}

void CorruptTest() {
	Data1 x {1, true, 2};
	std::stringstream streamx;
	streamx << "12 a 34";
	Deserializer deserializerx(streamx);
	const Error errx = deserializerx.load(x);
	assert(errx == Error::CorruptedArchive);
	assert(x.a == 12);
	assert(x.b == true);
	assert(x.c == 2);

	Data2 y {1};
	std::stringstream streamy;
	streamy << "true";
	Deserializer deserializery(streamy);
	const Error erry = deserializery.load(y);
	assert(erry == Error::CorruptedArchive);
	assert(y.a == 1);

	Data3 z {true};
	std::stringstream streamz;
	streamz << "1";
	Deserializer deserializerz(streamz);
	const Error errz = deserializerz.load(z);
	assert(errz == Error::CorruptedArchive);
	assert(z.a == true);

	Data2 k {1};
	std::stringstream streamk;
	streamk << "18446744073709551616";
	Deserializer deserializerk(streamk);
	const Error errk = deserializerk.load(k);
	assert(errk == Error::CorruptedArchive);
	assert(k.a == 1);

	Data2 l {1};
	std::stringstream streaml;
	const uint64_t checkl = 18446744073709551615UL;
	streaml << "18446744073709551615";
	Deserializer deserializerl(streaml);
	const Error errl = deserializerl.load(l);
	assert(errl == Error::NoError);
	assert(l.a == checkl);

	Data2 m {1};
	std::stringstream streamm;
	streamm << "123str";
	Deserializer deserializerm(streamm);
	const Error errm = deserializerm.load(m);
	assert(errm == Error::CorruptedArchive);
	assert(m.a == 1);

	Data3 n {true};
	std::stringstream streamn;
	streamm << "true12";
	Deserializer deserializern(streamn);
	const Error errn = deserializern.load(n);
	assert(errn == Error::CorruptedArchive);
	assert(n.a == true);
}

void ValidTest() {
	Data1 x {1, true, 2};
	std::stringstream streamx;
	streamx << "12 false 34";
	Deserializer deserializerx(streamx);
	const Error errx = deserializerx.load(x);
	assert(errx == Error::NoError);
	assert(x.a == 12);
	assert(x.b == false);
	assert(x.c == 34);

	Data2 y {1};
	std::stringstream streamy;
	streamy << "12";
	Deserializer deserializery(streamy);
	const Error erry = deserializery.load(y);
	assert(erry == Error::NoError);
	assert(y.a == 12);

	Data3 z {true};
	std::stringstream streamz;
	streamz << "false";
	Deserializer deserializerz(streamz);
	const Error errz = deserializerz.load(z);
	assert(errz == Error::NoError);
	assert(z.a == false);
}

void SingularTest() {
	Data2 x {0};
	std::stringstream streamx;
	Serializer serializerx(streamx);
	serializerx.save(x);
	assert(streamx.str() == "0 ");

	Data2 y {1};
	std::stringstream streamy;
	Serializer serializery(streamy);
	serializery.save(y);
	assert(streamy.str() == "1 ");

	Data2 z {2};
	std::stringstream streamz;
	streamz << "0";
	Deserializer deserializerz(streamz);
	const Error errz = deserializerz.load(z);
	assert(errz == Error::NoError);
	assert(z.a == 0);
	std::stringstream streamzz;
	streamzz << "1";
	Deserializer deserializerzz(streamzz);
	const Error errzz = deserializerzz.load(z);
	assert(errzz == Error::NoError);
	assert(z.a == 1);

	Data3 k {false};
	std::stringstream streamk;
	streamk << 0;
	Deserializer deserializerk(streamk);
	const Error errk = deserializerk.load(k);
	assert(errk == Error::CorruptedArchive);
	assert(k.a == false);
	std::stringstream streamkk;
	streamk << 1;
	Deserializer deserializerkk(streamkk);
	const Error errkk = deserializerkk.load(k);
	assert(errkk == Error::CorruptedArchive);
	assert(k.a == false);
}

void SerializerTest() {
	Data1 x {1, true, 23};
	std::stringstream streamx;
	Serializer serializerx(streamx);
	serializerx.save(x);
	assert(streamx.str() == "1 true 23 ");

	Data2 y {12};
	std::stringstream streamy;
	Serializer serializery(streamy);
	serializery.save(y);
	assert(streamy.str() == "12 ");

	Data3 z {true};
	std::stringstream streamz;
	Serializer serializerz(streamz);
	serializerz.save(z);
	assert(streamz.str() == "true ");
}

void LimitTest() {
	Data1 x {1, true, 2};
	std::stringstream streamx;
	streamx << "12 false";
	Deserializer deserializerx(streamx);
	Error errx = deserializerx.load(x);
	assert(errx == Error::CorruptedArchive);
	assert(x.a == 12);
	assert(x.b == false);
	assert(x.c == 2);

	std::stringstream streamxx;
	streamxx << "34 true 12 true";
	Deserializer deserializerxx(streamxx);
	Error errxx = deserializerxx.load(x);
	assert(errxx == Error::NoError);
	assert(x.a == 34);
	assert(x.b == true);
	assert(x.c == 12);

	Data2 y {1};
	std::stringstream streamy;
	streamy << "";
	Deserializer deserializery(streamy);
	Error erry = deserializery.load(y);
	assert(erry == Error::CorruptedArchive);
	assert(y.a == 1);

	std::stringstream streamyy;
	streamyy << "12 34";
	Deserializer deserializeryy(streamyy);
	Error erryy = deserializeryy.load(y);
	assert(erryy == Error::NoError);
	assert(y.a == 12);

	std::stringstream streamyyy;
	streamyyy << "12 false";
	Deserializer deserializeryyy(streamyyy);
	Error erryyy = deserializeryyy.load(y);
	assert(erryyy == Error::NoError);
	assert(y.a == 12);

	Data3 z {true};
	std::stringstream streamz;
	streamz << "";
	Deserializer deserializerz(streamz);
	Error errz = deserializerz.load(z);
	assert(errz == Error::CorruptedArchive);
	assert(z.a == true);

	std::stringstream streamzz;
	streamzz << "false true";
	Deserializer deserializerzz(streamzz);
	Error errzz = deserializerzz.load(z);
	assert(errzz == Error::NoError);
	assert(z.a == false);
}

int main() {
	DefaultTest();
	CorruptTest();
	ValidTest();
	SingularTest();
	SerializerTest();
	LimitTest();
	std::cout << "Success!" << std::endl;
	return 0;
}