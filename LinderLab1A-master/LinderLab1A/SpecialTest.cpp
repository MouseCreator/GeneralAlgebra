#include "doctest.h"

#include "FPolynomial.h"
#include "PositiveNumber.h"

#include <string>
#include <fstream>

class TestData {
private:
	std::vector<std::string> parameters;
	std::vector<std::string> result;
public:
	void addParamter(std::string parameter) {
		this->parameters.push_back(parameter);
	}
	std::string get(std::size_t i) {
		return parameters[i];
	}
	void addResult(std::string result) {
		this->result.push_back(result);
	}
	std::string getResult(std::size_t i) {
		return result[i];
	}
	std::size_t size() {
		return parameters.size();
	}
	std::size_t resultSize() {
		return result.size();
	}
};
//Runs more convenient tests for user
//Input: file, containing lines in format "param1, param2, ..., paramN => res1, ..., resM
// 
//Parameters are numbers that will be passed to number constructors
//Expected types of results:
//	AUTO : check result with some automatized case; in this case using classic algorithm to test Montgomery exponentiation
//	PRINT : prints result of the operation in console
//	number : check result with value given by user
// 
//Spaces and tabulation should not affect the executor
//There should be a line in format "modulo N", which will set the modulo of the field
//Otherwise the test will use value 97
class TestExecutor {
protected:
	std::vector<TestData> tests;
	FiniteField field;
	std::string sourceFile;
	bool noPrint = false;

	void processResult(TestData testData, std::string result) {

		for (std::size_t i = 0; i < testData.resultSize(); i++) {
			std::string expected = testData.getResult(i);
			if (expected == "AUTO") {
				autoCheck(result, testData);
			}
			else if (expected == "PRINT") {
				if (!noPrint)
					print(testData, result);
			}
			else {
				CHECK(result == expected);
			}
		}
	}
	virtual void print(TestData testData, std::string result) {
		std::cout << "Test case" << std::endl;
	}
	virtual void autoCheck(std::string result, TestData testData) {
	}
	virtual void execute(TestData testData) {
	}
private:
	std::string replaceAll(std::string origin, std::string target, std::string replacement) {
		int length = target.size();
		int replacementSize = replacement.size();
		std::size_t pos = origin.find(target);
		while (pos != std::string::npos)
		{
			origin.replace(pos, length, replacement);
			pos = origin.find(target, pos + replacementSize);
		}
		return origin;
	}
	std::string removeString(std::string origin, std::string target) {
		return replaceAll(origin, target, "");
	}

	bool contains(std::string origin, std::string target) {
		return origin.find(target) != std::string::npos;
	}

	std::string before(std::string origin, std::string target) {
		if (!contains(origin, target)) {
			return origin;
		}
		return origin.substr(0, origin.find(target));
	}
	std::string after(std::string origin, std::string target) {
		if (!contains(origin, target)) {
			return "";
		}
		return origin.substr(origin.find(target) + target.length());
	}

	void processString(std::string str) {
		std::string s = removeString(str, " ");
		s = removeString(s, "\t");
		if (contains(str, "modulo")) {
			s = removeString(s, "modulo");
			this->field.setP(PositiveNumber(s));
			return;
		}
		toTestData(s);
	}
	void toTestData(std::string s) {
		std::string paramterString = before(s, "=>");
		std::string resultString = after(s, "=>");
		TestData testData;
		createParameters(testData, paramterString);
		createResult(testData, resultString);
		this->tests.push_back(testData);
	}
	void createParameters(TestData& testData, std::string str) {
		if (str.empty())
			return;
		while (contains(str, ",")) {
			testData.addParamter(before(str, ","));
			str = after(str, ",");
		}
		testData.addParamter(str);
	}
	void createResult(TestData& testData, std::string str) {
		if (str.empty())
			return;
		while (contains(str, ",")) {
			testData.addResult(before(str, ","));
			str = after(str, ",");
		}
		testData.addResult(str);
	}

public:
	TestExecutor() {

	}

	void setPrintable(bool isPrintable) {
		this->noPrint = !isPrintable;
	}

	void readTestData() {
		std::ifstream f;
		f.open(sourceFile);
		std::string line;
		TestExecutor tests;
		while (f.good()) {
			getline(f, line);
			processString(line);
		}
		f.close();
	}
	std::size_t getNumberOfTests() {
		return tests.size();
	}

	void execute(std::size_t testNumber) {
		if (testNumber >= tests.size()) {
			return;
		}
		TestData testData = TestExecutor::tests[testNumber];
		execute(testData);
	}
	void executeAll() {
		for (TestData t : tests) {
			execute(t);
		}
	}
};
//Special tests for Exponent
//Input file format: "base, power => result"
class ExponentTestExecutor : TestExecutor {
private:
	Exponentiation exp;
	void autoCheck(std::string expected, TestData testData) {
		FiniteNumber base = FiniteNumber(testData.get(0), TestExecutor::field.getP());
		PositiveNumber power = PositiveNumber(testData.get(1));
		FiniteNumber result = exp.fastExponentiation(base, power);
		CHECK(expected == result.toString());
	}
	void print(TestData testData, std::string result) {
		std::cout << testData.get(0) << " ^ " << testData.get(1) << " = " << result
			<< " (mod " << field.getP().toString() << ")" << std::endl;
	}
	void execute(TestData testData) {
		if (testData.size() != 2) {
			return;
		}
		FiniteNumber base = FiniteNumber(testData.get(0), TestExecutor::field.getP());
		PositiveNumber power = PositiveNumber(testData.get(1));
		FiniteNumber result = exp.montgomeryExponentiation(base, power);
		return processResult(testData, result.toString());
	}
public:
	ExponentTestExecutor() : TestExecutor() {
		this->sourceFile = "../Special exponent test.txt";
		field.setP(PositiveNumber("97"));
	}
	void readTestData() {
		TestExecutor::readTestData();
	}
	void executeAll() {
		TestExecutor::executeAll();
	}
	std::size_t getNumberOfTests() {
		return TestExecutor::getNumberOfTests();
	}
	void execute(std::size_t testNumber) {
		TestExecutor::execute(testNumber);
	}
	void setPrintable(bool v) {
		TestExecutor::setPrintable(v);
	}
};

class BasicOperationTestExecutor : TestExecutor {
private:
	void print(TestData testData, std::string result) {
		std::cout << testData.get(1) << " " << testData.get(0) << " " << testData.get(2) << " = " << result
			<< " (mod " << field.getP().toString() << ")" << std::endl;
	}
public:
	BasicOperationTestExecutor() : TestExecutor() {
		this->sourceFile = "../Basic operation special test.txt";
		field.setP(PositiveNumber("97"));
	}
	void readTestData() {
		TestExecutor::readTestData();
	}
	void executeAll() {
		TestExecutor::executeAll();
	}
	std::size_t getNumberOfTests() {
		return TestExecutor::getNumberOfTests();
	}
	void execute(std::size_t testNumber) {
		TestExecutor::execute(testNumber);
	}
	void execute(TestData testData) {
		if (testData.size() != 3) {
			return;
		}
		char operation = testData.get(0)[0];
		FiniteNumber operand1 = FiniteNumber(testData.get(1), TestExecutor::field.getP());
		FiniteNumber operand2 = FiniteNumber(testData.get(2), TestExecutor::field.getP());
		FiniteNumber result;
		switch (operation) {
		case '+': result = operand1 + operand2; break;
		case '-': result = operand1 - operand2; break;
		case '*': result = operand1 * operand2; break;
		case '/': result = operand1 / operand2; break;
		default: return;
		}
		return processResult(testData, result.toString());
	}
	void setPrintable(bool v) {
		TestExecutor::setPrintable(v);
	}
};

class InverseNumberTestExecutor : TestExecutor {
private:
	void autoCheck(std::string expected, TestData testData) {
		FiniteNumber base = FiniteNumber(testData.get(0), this->field.getP());
		FiniteNumber a = base.inverse();
		FiniteNumber b = a.inverse();
		CHECK(base.toString() == b.toString());
	}
	void print(TestData testData, std::string result) {
		std::cout << "Inverse of " << testData.get(0) << " is " << result << " (mod " << field.getP().toString() << ")" << std::endl;
	}
public:
	InverseNumberTestExecutor() : TestExecutor() {
		this->sourceFile = "../Inverse special test.txt";
		field.setP(PositiveNumber("97"));
	}
	void readTestData() {
		TestExecutor::readTestData();
	}
	void executeAll() {
		TestExecutor::executeAll();
	}
	std::size_t getNumberOfTests() {
		return TestExecutor::getNumberOfTests();
	}
	void execute(std::size_t testNumber) {
		TestExecutor::execute(testNumber);
	}
	void execute(TestData testData) {
		if (testData.size() != 1) {
			return;
		}
		FiniteNumber operand1 = FiniteNumber(testData.get(0), TestExecutor::field.getP());
		FiniteNumber result = operand1.inverse();
		return processResult(testData, result.toString());
	}
	void setPrintable(bool v) {
		TestExecutor::setPrintable(v);
	}
};

TEST_SUITE("Special") {

	bool printResult = false;

	//Tests by M. Tyshchenko
	TEST_CASE("Special Exponent Test") {
		ExponentTestExecutor executor;
		executor.setPrintable(printResult);
		executor.readTestData();
		executor.executeAll();
	}

	//Tests by M. Tyshchenko
	TEST_CASE("Special Basic Operation Test") {
		BasicOperationTestExecutor executor;
		executor.setPrintable(printResult);
		executor.readTestData();
		executor.executeAll();
	}

	//Tests by M. Tyshchenko
	TEST_CASE("Special Inverse Number Test") {
		InverseNumberTestExecutor executor;
		executor.setPrintable(printResult);
		executor.readTestData();
		executor.executeAll();
	}
}

