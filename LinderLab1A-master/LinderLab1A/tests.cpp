#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "SignedNumber.h"
#include "FiniteNumber.h"
//#include "Exponent.h"
#include "Polynomial.h"
#include "FiniteGroup.h"
#include "CalculationOfSquareRoot.h"
#include "MillerRabin.h"
//#include "Pollard.h"
#include "Euler.h"

#include <random>
#include <string>
#include <chrono>
#include <fstream>
//Test by M. Tyshchenko
TEST_CASE("Positive numbers") {
	std::ifstream f;
	f.open("../Positive numbers Test.txt");

	//PositiveNumber a = PositiveNumber("1234");
	//PositiveNumber b = PositiveNumber("99");
	std::string aStr,bStr;
	f >> aStr >> bStr;
	PositiveNumber a(aStr);
	PositiveNumber b(bStr);
	CHECK((a * b).toString() == "122166");
	CHECK((b * a).toString() == "122166");
	CHECK((a - b).toString() == "1135");
	CHECK((b - a).toString() == "1135");
	CHECK((b + a).toString() == "1333");
	CHECK((a + b).toString() == "1333");

	f.close();
}

//Test by V.Avramenko
TEST_CASE("Division Test for PositiveNumber") {
	std::ifstream f;
	f.open("../Division Test for PositiveNumber.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;

	PositiveNumber p1(p1Str);
	PositiveNumber p2(p2Str);
	PositiveNumber p3 = p1 / p2;
	CHECK(p3.toString() == "4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("1008");
	p2 = PositiveNumber("23");
	p3 = p1 / p2;
	CHECK(p3.toString() == "43");
	p1 = PositiveNumber("669999");
	p2 = PositiveNumber("257");
	p3 = p1 / p2;
	CHECK(p3.toString() == "2607");
	f.close();
}

//Test by V.Avramenko
TEST_CASE("Division Test for SignedNumber") {
	std::ifstream f;
	f.open("../Division Test for SignedNumber.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;
	SignedNumber p1(p1Str);
	SignedNumber p2(p2Str);
	SignedNumber p3 = p1 / p2;
	CHECK(p3.toString() == "-4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("-16");
	p2 = SignedNumber("3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "-5");
	p1 = SignedNumber("-11");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "3");
	p1 = SignedNumber("2");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "0");
	f.close();
}

//Test by V.Avramenko
TEST_CASE("Remainder Test for Positive Numbers") {
	std::ifstream f;
	f.open("../Remainder Test for Positive Numbers.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;

	PositiveNumber p1(p1Str);
	PositiveNumber p2(p2Str);
	PositiveNumber p3 = p1 % p2;
	CHECK(p3.toString() == "2");
	p1 = PositiveNumber("102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "6");
	p2 = PositiveNumber("2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("7");
	p2 = PositiveNumber("8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
	f.close();
}

//Test by V.Avramenko
TEST_CASE("Remainder Test for Signed Numbers") {
	std::ifstream f;
	f.open("../Remainder Test for Signed Numbers.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;
	SignedNumber p1(p1Str);
	SignedNumber p2(p2Str);
	SignedNumber p3 = p1 % p2;
	CHECK(p3.toString() == "-2");
	p1 = SignedNumber("-102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-6");
	p2 = SignedNumber("-2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("7");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
	p1 = SignedNumber("-9");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-1");
}

//Test by M. Tyshchenko
TEST_CASE("Test on random numbers") {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0, 5000);
	for (int i = 0; i < 200; i++) {
		int a = distr(generator);
		int b = distr(generator);
		PositiveNumber aNum = PositiveNumber(std::to_string(a));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK((aNum + bNum).toString() == std::to_string(a + b));
		CHECK((aNum - bNum).toString() == std::to_string(abs(a - b)));
		CHECK((aNum * bNum).toString() == std::to_string(a * b));
		if (b != 0) {
			CHECK((aNum / bNum).toString() == std::to_string(a / b));
			CHECK((aNum % bNum).toString() == std::to_string(a % b));
		}
	}
}

//Tests by M. Tyshchenko
TEST_CASE("Signed numbers") {

	std::ifstream f;
	f.open("../Signed numbers Test.txt");
	std::string finiteStr, signedNStr, signedMStr,aStr,bStr;
	getline(f, finiteStr);
	f >> signedNStr >> signedMStr>>aStr>>bStr;
	
	FiniteNumber finite = FiniteNumber(finiteStr);
	CHECK(finite.toString() == "4");
	SignedNumber signedN = SignedNumber(signedNStr);
	SignedNumber signedM = SignedNumber(signedMStr);
	SignedNumber res = signedN;
	res -= signedM;
	CHECK(res.toString() == "1855");


	SignedNumber a = SignedNumber(aStr);
	SignedNumber b = SignedNumber(bStr);
	SignedNumber c = a * b;
	CHECK(c.toString() == "0");
	f.close();

}
//Testing FiniteNumbers by Vlad Avramenko
TEST_CASE("Finite numbers") {
	std::ifstream f;
	f.open("../Finite numbers Tests.txt");
	std::string fin1Str, fin2Str,origStr;
	getline(f, fin1Str);
	getline(f, fin2Str);
	FiniteNumber fin1 = FiniteNumber(fin1Str);
	FiniteNumber fin2 = FiniteNumber(fin2Str);
	CHECK(fin1.toString() == "6");
	CHECK(fin2.toString() == "6");
	FiniteNumber fin3 = fin1 + fin2;
	CHECK(fin3.toString() == "2");
	fin1 += fin2;
	CHECK(fin1.toString() == "2");
	fin3 = fin1 - fin2;
	CHECK(fin3.toString() == "6");
	fin1 -= fin2;
	CHECK(fin1.toString() == "6");
	fin3 = fin1 * fin2;


	

	CHECK(fin3.toString() == "6");
	getline(f, origStr);
	FiniteNumber orig = FiniteNumber(origStr);


	FiniteNumber inv = orig.inverse();
	CHECK(inv.toString() == "3");
	getline(f, fin1Str);
	getline(f, fin2Str);
	fin1 = FiniteNumber(fin1Str);
	fin2 = FiniteNumber(fin2Str);
	FiniteNumber fin4 = fin1 / fin2;
	FiniteNumber fin5 = fin2 / fin1;
	CHECK(fin4.toString() == "8");
	CHECK(fin5.toString() == "3");
	fin1.divideBy(fin2);
	CHECK(fin1.toString() == "8");
	getline(f, fin1Str);
	getline(f, fin2Str);
	fin1 = FiniteNumber(fin1Str);
	fin2 = FiniteNumber(fin2Str);

	auto res = fin1 + fin2;
	CHECK(res.toString() == "1127822179038104809524733176879403005056");

	fin1 = FiniteNumber("-1232 x10");
	CHECK(fin1.toString() == "8");

	fin1 = FiniteNumber("-10 x6");
	CHECK(fin1.toString() == "2");

	fin1 = FiniteNumber("-1 x10");
	CHECK(fin1.toString() == "9");

	fin1 = FiniteNumber("-6 x6");
	CHECK(fin1.toString() == "0");

	fin1 = FiniteNumber("-6 x5");
	CHECK(fin1.toString() == "4");
	f.close();
}

//Tests by M. Tyshchenko
TEST_CASE("Test zero") {
	std::ifstream f;
	f.open("../Test zero.txt");
	std::string zeroStr, aStr, bStr;
	f >> zeroStr >> aStr >> bStr;
	PositiveNumber zero = PositiveNumber(zeroStr);
	PositiveNumber a = PositiveNumber(aStr);
	PositiveNumber b = PositiveNumber(bStr);
	CHECK(a * b == zero);
	CHECK(b * a == zero);
	f.close();
}

//Tests for exponentiation by M. Tyshchenko
TEST_CASE("Exponent") {
	std::ifstream f;
	f.open("../Exponent Test.txt");
	std::string nStr, mStr, aNStr, toMultiplyStr, toMultiply2Str,baseStr,powerStr;
	getline(f, nStr);
	getline(f, mStr);
	getline(f, aNStr);
	getline(f, toMultiplyStr);
	getline(f, toMultiply2Str);
	
	FiniteNumber n = FiniteNumber(nStr);
	FiniteNumber m = FiniteNumber(mStr);
	CHECK(n.toString() == "15");
	CHECK((n * m).toString() == "5");
	CHECK((m * n).toString() == "5");

	PositiveNumber aN = PositiveNumber("15");
	CHECK((aN.shift(2)).toString() == "1500");
	CHECK((aN.shift(-2)).toString() == "0");
	CHECK(FiniteNumber("x257 10000").inverse().toString() == "67");

	FiniteNumber toMultiply = FiniteNumber(toMultiplyStr);
	FiniteNumber toMultiply2 = FiniteNumber(toMultiply2Str);
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	CHECK(result.toString() == "217");
	getline(f, toMultiplyStr);
	getline(f, toMultiply2Str);
	getline(f, baseStr);
	getline(f, powerStr);
	toMultiply = FiniteNumber(toMultiplyStr);
	toMultiply2 = FiniteNumber(toMultiply2Str);
	CHECK(exp.montgomeryMultiplication(toMultiply, toMultiply2).toString() == "58");

	FiniteNumber base = FiniteNumber("x257 30");
	PositiveNumber power = PositiveNumber("5");
	result = exp.montgomeryExponentiation(base, power);
	CHECK(result.toString() == "136");

	getline(f, baseStr);
	getline(f, powerStr);
	base = FiniteNumber(baseStr);
	power = PositiveNumber(powerStr);
	result = exp.montgomeryExponentiation(base, power);

	CHECK(result.toString() == "8");

	getline(f, baseStr);
	getline(f, powerStr);
	base = FiniteNumber(baseStr);
	power = PositiveNumber(powerStr);
	std::string expected = "839534";
	//TIMING
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	CHECK(exp.montgomeryExponentiation(base, power).toString() == expected);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Montgomery = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;

	begin = std::chrono::steady_clock::now();
	CHECK(exp.fastExponentiation(base, power).toString() == expected);
	end = std::chrono::steady_clock::now();
	//std::cout << "Fast = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;

	//begin = std::chrono::steady_clock::now();
	//CHECK(exp.slowExponention(base, power).toString() == expected);
	//end = std::chrono::steady_clock::now();
	//std::cout << "Slow = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;
	f.close();



	base = FiniteNumber("x5 9");
	power = PositiveNumber("1");
	FiniteNumber res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "4");

	base = FiniteNumber("x2 1");
	power = PositiveNumber("8");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "1");

	base = FiniteNumber("x2 0");
	power = PositiveNumber("0");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "1");

	base = FiniteNumber("x2 0");
	power = PositiveNumber("100");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "0");

	base = FiniteNumber("x7 4");
	power = PositiveNumber("10");
	expected = "4";
	CHECK(exp.montgomeryExponentiation(base, power).toString() == expected);

	f.close();


}

TEST_CASE("Exponentiation on random values") {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> baseDistr(0, 2000);
	std::uniform_int_distribution<int> powDistr(0, 20);
	Exponentiation exponent;
	for (int i = 0; i < 200; i++) {
		int a = baseDistr(generator);
		int b = powDistr(generator);
		FiniteNumber aNum = FiniteNumber(std::to_string(a), PositiveNumber("197"));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK(exponent.montgomeryExponentiation(aNum, bNum).toString() == exponent.slowExponentiation(aNum, bNum).toString());
	}
}
//Tests for bits function
TEST_CASE("Test binary form") {
	std::ifstream f;
	f.open("../Test binary form.txt");
	std::string aStr;
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "101");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "0");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "1100100");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "100");
	f.close();
}

//Created by Y.Kishchuk
TEST_CASE("Test setIdentity and getIdentity methods") {
	FiniteGroup group(PositiveNumber("10"));

	group.setIdentity(FiniteNumber("0 x10"));
	CHECK(group.getIdentity() == FiniteNumber("0 x10"));
	CHECK(group.getIdentity() == FiniteNumber("0 x10"));
	group.setIdentity(FiniteNumber("1 x10"));
	CHECK(group.getIdentity() == FiniteNumber("1 x10"));
}

TEST_CASE("Test setGroupBinaryOperation method") {
	FiniteGroup group(PositiveNumber("10"));

	// Test if the binary operation is set correctly
	CHECK(group.operate(FiniteNumber("2 x10"), FiniteNumber("3 x10")) == FiniteNumber("6 x10"));
}

TEST_CASE("Test getP method") {
	FiniteGroup group(PositiveNumber("10"));

	auto ten = PositiveNumber("10");
	CHECK(group.getP().equals(ten));

	// Test getP method with a different modulus
	FiniteGroup group2(PositiveNumber("7"));
	auto seven = PositiveNumber("7");
	CHECK(group2.getP() == seven);
}

TEST_CASE("Test ElementOrder method") {
	FiniteGroup group(PositiveNumber("7"));
	group.setIdentity(FiniteNumber("1 x7"));

	// Test ElementOrder method
	CHECK_THROWS_AS(group.ElementOrder(FiniteNumber("0 x7")).toString(), std::runtime_error);
	CHECK(group.ElementOrder(FiniteNumber("1 x7")).toString() == PositiveNumber("1").toString());
	CHECK(group.ElementOrder(FiniteNumber("2 x7")).toString() == PositiveNumber("3").toString());
	CHECK(group.ElementOrder(FiniteNumber("3 x7")).toString() == PositiveNumber("6").toString());
	CHECK(group.ElementOrder(FiniteNumber("4 x7")).toString() == PositiveNumber("3").toString());
	CHECK(group.ElementOrder(FiniteNumber("5 x7")).toString() == PositiveNumber("6").toString());
	CHECK(group.ElementOrder(FiniteNumber("6 x7")).toString() == PositiveNumber("2").toString());

	auto group2 = FiniteGroup(PositiveNumber("11"));
	group2.setIdentity(FiniteNumber("1 x11"));
	CHECK_THROWS_AS(group2.ElementOrder(FiniteNumber("0 x11")).toString(), std::runtime_error);
	CHECK(group2.ElementOrder(FiniteNumber("1 x11")).toString() == PositiveNumber("1").toString());
	CHECK(group2.ElementOrder(FiniteNumber("2 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("3 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("4 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("5 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("6 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("7 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("8 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("9 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("10 x11")).toString() == PositiveNumber("2").toString());

	auto group3 = FiniteGroup(PositiveNumber("10"));
	group3.setIdentity(FiniteNumber("1 x10"));
	CHECK(group3.ElementOrder(FiniteNumber("1 x10")).toString() == PositiveNumber("1").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("2 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("3 x10")).toString() == PositiveNumber("4").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("4 x10")).toString(), std::overflow_error);
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("5 x10")).toString(), std::overflow_error);
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("6 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("7 x10")).toString() == PositiveNumber("4").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("8 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("9 x10")).toString() == PositiveNumber("2").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("10 x10")).toString(), std::overflow_error);
}

//Test by T. Pysarenkov
TEST_CASE("Test isGenerator method") {
	FiniteGroup g1(PositiveNumber("x7"));
	g1.setIdentity(FiniteNumber("1 x7"));
	CHECK(!g1.isGenerator(FiniteNumber("1 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("2 x7")));
	CHECK(g1.isGenerator(FiniteNumber("3 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("4 x7")));
	CHECK(g1.isGenerator(FiniteNumber("5 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("6 x7")));

	FiniteGroup g2(PositiveNumber("x11"));
	g2.setIdentity(FiniteNumber("1 x11"));
	CHECK(!g2.isGenerator(FiniteNumber("1 x11")));
	CHECK(g2.isGenerator(FiniteNumber("2 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("3 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("4 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("5 x11")));
	CHECK(g2.isGenerator(FiniteNumber("6 x11")));
	CHECK(g2.isGenerator(FiniteNumber("7 x11")));
	CHECK(g2.isGenerator(FiniteNumber("8 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("9 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("10 x11")));

	FiniteGroup g3(PositiveNumber("x9"));
	g3.setIdentity(FiniteNumber("1 x9"));
	CHECK(!g3.isGenerator(FiniteNumber("1 x9")));
	CHECK(g3.isGenerator(FiniteNumber("2 x9")));
	CHECK_THROWS_AS(g3.isGenerator(FiniteNumber("3 x9")), std::runtime_error);
	CHECK(!g3.isGenerator(FiniteNumber("4 x9")));
	CHECK(g3.isGenerator(FiniteNumber("5 x9")));
	CHECK_THROWS_AS(g3.isGenerator(FiniteNumber("6 x9")), std::runtime_error);
	CHECK(!g3.isGenerator(FiniteNumber("7 x9")));
	CHECK(!g3.isGenerator(FiniteNumber("8 x9")));
}

//Tests by P. Velychko #6
TEST_CASE("TestNonQuadraticPositive") {
	std::ifstream f;
	f.open("../TestNonQuadraticPositive.txt");
	std::string aStr;
	getline(f, aStr);
	long long a(stoi(aStr));

	FiniteNumber one("1", 19);

	long long x(CalculationOfSquareRoot::power_mod(a, (19 - 1) / 2, 19));


	if (x != 1) {
		cout << "a is not a quadratic residue mod p" << endl;
	}
	else {
		long long root(CalculationOfSquareRoot::tonelli_shanks(a, 19));

		CHECK(CalculationOfSquareRoot::power_mod(root, 2, 19) == a);
	}
	f.close();
}

TEST_CASE("TestQuadraticResidue1") {
	std::ifstream f;
	f.open("../TestQuadraticResidue1.txt");
	std::string aStr;
	getline(f, aStr);
	long long a(stoi(aStr));
	int b = 5;
	FiniteNumber one("1", 11);

	long long x(CalculationOfSquareRoot::power_mod(a,(11-1)/2,11));

	if (x != 1) {
		cout << "a is not a quadratic residue mod p" << endl;

	}
	else {
		long long root(CalculationOfSquareRoot::tonelli_shanks(a,11));
		CHECK(root == 5);
	}
	f.close();

}

TEST_CASE("TestQuadraticResidue2") {
	
	std::ifstream f;
	f.open("../TestQuadraticResidue2.txt");
	std::string aStr;
	getline(f, aStr);
	long long a(stoi(aStr));
	
	FiniteNumber one("1", 19);

	long long x(CalculationOfSquareRoot::power_mod(a, (19 - 1) / 2, 19));


	if (x != 1) {
		cout << "a is not a quadratic residue mod p" << endl;

	}
	else {
		long long root(CalculationOfSquareRoot::tonelli_shanks(a, 19));

		CHECK(CalculationOfSquareRoot::power_mod(root,2,19) == a);
	}
	f.close();
}

TEST_CASE("Test Integer Constuctors") {
	std::ifstream f;
	f.open("../Test Integer Constuctors.txt");
	std::string aStr, bStr;
	f >> aStr >> bStr;
	int aInt = std::stoi(aStr);
	int bInt = std::stoi(bStr);
	PositiveNumber a = PositiveNumber(aInt);
	PositiveNumber b = PositiveNumber(bInt);
	CHECK("64" == (a + b).toString());
	
	FiniteNumber finite1 = FiniteNumber(18, 17);
	CHECK("1" == finite1.toString());
	f.close();
}

TEST_CASE("Additional operators test") {
	std::ifstream f;
	f.open("../Additional operators test.txt");
	std::string aStr, bStr,cStr,dStr;
	getline(f, aStr);
	getline(f, bStr);
	getline(f, cStr);
	getline(f, dStr);
	FiniteNumber a = FiniteNumber(aStr);
	FiniteNumber b = FiniteNumber(bStr);
	FiniteNumber c = FiniteNumber(cStr);
	FiniteNumber d = FiniteNumber(dStr);
	CHECK(a == b);
	CHECK(a != c);
	CHECK(a != d);
	f.close();
}

TEST_CASE("Additional operators") {
	std::ifstream f;
	f.open("../Additional operators.txt");
	std::string aStr, bStr;
	getline(f, aStr);
	getline(f, bStr);
	FiniteNumber a = FiniteNumber(aStr);
	FiniteNumber b = FiniteNumber(bStr);
	CHECK(a > b);
	CHECK(b < a);
	CHECK(!(a < b));
	CHECK(!(b > a));
	f.close();
}

TEST_CASE("Modular Power") {
	std::ifstream f;
	f.open("../Modular Power.txt");
	std::string aStr, bStr,cStr;
	getline(f, aStr);
	getline(f, bStr);
	getline(f, cStr);
	PositiveNumber a = PositiveNumber(aStr);
	PositiveNumber b = PositiveNumber(bStr);
	PositiveNumber c = PositiveNumber(cStr);
	auto result = mod_power(a, b, c).toString();
	CHECK("9" == result);
}

TEST_CASE("Miller-Rabin Primality Test") {
	std::ifstream f;
	f.open("../Miller-Rabin Primality Test.txt");
	std::string aStr;
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f.close();

}

TEST_CASE("Naive Factorization") {
	std::ifstream f;
	f.open("../Naive Factorization.txt");
	std::string a1Str,a2Str,a3Str;
	f >> a1Str >> a2Str >> a3Str;
	PositiveNumber a1 = PositiveNumber(a1Str);
	std::map<PositiveNumber, int> result1 = map_factors(a1, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = { std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };

	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(a2Str);
	std::map<PositiveNumber, int> result2 = map_factors(a2, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(a3Str);
	std::map<PositiveNumber, int> result3 = map_factors(a3, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);
	f.close();

}

TEST_CASE("Pollard's Rho Factorization") {
	std::ifstream f;
	f.open("../Pollard's Rho Factorization.txt");
	std::string a1Str, a2Str, a3Str;
	f >> a1Str >> a2Str >> a3Str;
	PositiveNumber a1 = PositiveNumber(a1Str);
	std::map<PositiveNumber,int> result1 = map_factors(a1, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = {std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };
	
	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(a2Str);
	std::map<PositiveNumber, int> result2 = map_factors(a2, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(a3Str);
	std::map<PositiveNumber, int> result3 = map_factors(a3, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);
	f.close();
}

TEST_CASE("Euler For Prime Values")
{
	std::ifstream f;
	f.open("../Euler For Prime Values.txt");
	std::string value1Str, value2Str, degree2Str;
	f >> value1Str >> value2Str >> degree2Str;

	PositiveNumber value1(value1Str);
	PositiveNumber answer1("1");

	PositiveNumber value2(value2Str);
	PositiveNumber degree2(degree2Str);
	PositiveNumber answer2("11638");

	CHECK(EulerForPrimeValues(value1) == answer1);
	CHECK(EulerForPrimeValues(value2, degree2) == answer2);
	f.close();
}

TEST_CASE("Euler")
{
	std::ifstream f;
	f.open("../Euler.txt");
	std::string value1Str, value2Str, value3Str, value4Str;
	f >> value1Str >> value2Str >> value3Str >> value4Str;
	PositiveNumber value1(value1Str);
	PositiveNumber value2(value2Str);
	PositiveNumber value3(value3Str);
	PositiveNumber value4(value4Str);

	CHECK(Euler(value1).toString() == "12");
	CHECK(Euler(value2).toString() == "4027392");
	CHECK(Euler(value3).toString() == "32");
	CHECK(Euler(value4).toString() == "1");
	f.close();
}

TEST_CASE("Carmichel")
{
	std::ifstream f;
	f.open("../Carmichel.txt");
	std::string value1Str, value2Str, value3Str, value4Str;
	f >> value1Str >> value2Str >> value3Str >> value4Str;
	PositiveNumber value1("9");
	PositiveNumber value2("32");
	PositiveNumber value3("36");
	PositiveNumber value4("169");

	CHECK(Carmichel(value1).toString() == "6");
	CHECK(Carmichel(value2).toString() == "8");
	CHECK(Carmichel(value3).toString() == "6");
	CHECK(Carmichel(value4).toString() == "156");
	f.close();
}