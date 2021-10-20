#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <any>

#include "exceptions.hpp"
#include "StringUtilities.h"

enum class clOptionType {
	BOOLEAN,
	STRING,
	INT32,
	DOUBLE,
	UINT32
};

class clOptionIdentifier {
public:
	clOptionIdentifier(const std::string& szVerbose, const std::string& szAbbr, int32_t nPos)
		:m_szVerbose{ szVerbose }, m_szAbbr{ szAbbr }, m_nPos{ nPos }{}
	clOptionIdentifier(){}
	~clOptionIdentifier(){}

	std::string Verbose() { return m_szVerbose; }
	std::string Abbr() { return m_szAbbr; }
	int32_t Pos() { return m_nPos; }

	std::string ToString() {
		return m_szVerbose + " | " + m_szAbbr + " | " + std::to_string(m_nPos);
	}

private:
	std::string m_szVerbose;
	std::string m_szAbbr;
	int32_t m_nPos{ -1 };
};

class clOptionValue {
public:
	clOptionValue(clOptionType type, std::any value)
		:m_type{ type }, m_value{ value }{}
	~clOptionValue(){}

	bool GetBooleanOption(bool& out) {
		if (m_type == clOptionType::BOOLEAN && m_value.type() == typeid(bool)) {
			out = std::any_cast<bool>(m_value);
			return true;
		}
		else {
			return false;
		}
	}

	bool GetStringOption(std::string& out) {
		if (m_type == clOptionType::STRING && m_value.type() == typeid(std::string)) {
			out = std::any_cast<std::string>(m_value);
			return true;
		}
		else {
			return false;
		}
	}

	bool GetIntegerOption(int32_t& out) {
		if (m_type == clOptionType::INT32 && m_value.type() == typeid(int32_t)) {
			out = std::any_cast<int32_t>(m_value);
			return true;
		}
		else {
			return false;
		}
	}

	bool GetUnsignedIntegerOption(uint32_t& out) {
		if (m_type == clOptionType::UINT32 && m_value.type() == typeid(uint32_t)) {
			out = std::any_cast<uint32_t>(m_value);
			return true;
		}
		else {
			return false;
		}
	}

	bool GetDoubleOption(double& out) {
		if (m_type == clOptionType::BOOLEAN && m_value.type() == typeid(double)) {
			out = std::any_cast<double>(m_value);
			return true;
		}
		else {
			return false;
		}
	}

	void SetOption(const std::string& szValue) {
		/* throws std::invalid_argument, std::out_of_range */
		if (m_type == clOptionType::BOOLEAN) {
			m_value = static_cast<bool>(std::stoi(szValue));
		}
		else if (m_type == clOptionType::INT32) {
			m_value = static_cast<int32_t>(std::stoi(szValue));
		}
		else if (m_type == clOptionType::UINT32) {
			m_value = static_cast<uint32_t>(std::stoul(szValue));
		}
		else if (m_type == clOptionType::DOUBLE) {
			m_value = std::stod(szValue);
		}
		else {
			m_value = szValue;
		}
	}

	bool SetFlag() {
		if (m_type == clOptionType::BOOLEAN) {
			m_value = true;
			return true;
		}
		return false;
	}

private:
	clOptionType m_type;
	std::any m_value;
};

class clOption {
public:
	clOption(const std::string& szVerbose, const std::string& szAbbr, int32_t nPos, clOptionType type, std::any value)
		:m_id(szVerbose, szAbbr, nPos), m_value(type, value){}
	clOption(clOptionIdentifier& id, clOptionValue& value)
		:m_id{ id }, m_value{ value }{}
	~clOption(){}

	bool MatchAny(clOption option) {
		if (MatchAbbr(option.m_id.Abbr())) {
			return MatchVerboseOrEmpty(option.m_id.Verbose()) && MatchPosOrNegative(option.m_id.Pos());
		}
		if (MatchVerbose(option.m_id.Verbose())) {
			return MatchAbbrOrEmpty(option.m_id.Abbr()) && MatchPosOrNegative(option.m_id.Pos());
		}
		if (MatchPos(option.m_id.Pos())) {
			return MatchVerboseOrEmpty(option.m_id.Verbose()) && MatchAbbrOrEmpty(option.m_id.Abbr());
		}
		return false;
	}

	bool MatchVerbose(const std::string& szOption) {
		return m_id.Verbose() == szOption && szOption != "";
	}

	bool MatchAbbr(const std::string& szOption) {
		return m_id.Abbr() == szOption && szOption != "";
	}

	bool MatchPos(int32_t nPos) {
		return m_id.Pos() == nPos && nPos >= 0;
	}

	bool MatchVerboseOrEmpty(const std::string& szOption) {
		return m_id.Verbose() == szOption || m_id.Verbose().empty();
	}

	bool MatchAbbrOrEmpty(const std::string& szOption) {
		return m_id.Abbr() == szOption || m_id.Abbr().empty();
	}

	bool MatchPosOrNegative(int32_t nPos) {
		return m_id.Pos() == nPos || m_id.Pos() < 0;
	}

	bool GetBooleanOption(bool& out) {
		return m_value.GetBooleanOption(out);
	}

	bool GetStringOption(std::string& out) {
		return m_value.GetStringOption(out);
	}

	bool GetIntegerOption(int32_t& out) {
		return m_value.GetIntegerOption(out);
	}

	bool GetUnsignedIntegerOption(uint32_t& out) {
		return m_value.GetUnsignedIntegerOption(out);
	}

	bool GetDoubleOption(double& out) {
		return m_value.GetDoubleOption(out);
	}

	void SetOption(const std::string& szValue) {
		try {
			m_value.SetOption(szValue);
		}
		catch (std::invalid_argument) {
			throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "invalid argument type provided for option: " + m_id.ToString(), Severity().CRITICAL());
		}
		catch (std::out_of_range) {
			throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "invalid argument type provided for option: " + m_id.ToString(), Severity().CRITICAL());
		}
	}

	void SetFlag() {
		if (!m_value.SetFlag()) {
			throw ExceptionBuilder().Build(ExceptionTypes().NOT_SUPPORTED(), "argument requires value when explicitly provided " + m_id.ToString(), Severity().CRITICAL());
		}
	}

private:
	clOptionValue m_value;
	clOptionIdentifier m_id;

};

class _clArgs {
public:
	_clArgs() {}
	~_clArgs() {}

	/* Destructive, call only once per _clArgs object */
	std::shared_ptr<_clArgs> Fill(int argc, char** argv) {
		std::shared_ptr<_clArgs> unregistered = std::make_shared<_clArgs>();
		if (argc > 0) {
			bool bHadExplicitOption{ false };
			std::string szPrevOption{ "" };
			for (int i = 0; i < argc; i++) {
				if (StringUtilities().startsWith(argv[i], "--") || StringUtilities().startsWith(argv[i], "-")) {
					bHadExplicitOption = true;
					if (szPrevOption.empty()) {
						szPrevOption = argv[i];
						continue;
					}
					else {
						if (StringUtilities().startsWith(szPrevOption, "--")) {
							if (!SetFlagVerbose(szPrevOption)) {
								unregistered->RegisterBooleanOption(szPrevOption, "", -1, true);
							}
						}
						else {
							if (!SetFlagAbbr(szPrevOption)) {
								unregistered->RegisterBooleanOption("", szPrevOption, -1, true);
							}
						}
						szPrevOption = argv[i];
					}
				}
				else {
					if (!bHadExplicitOption) {
						if (!SetOptionPos(i, argv[i])) {
							unregistered->RegisterStringOption("", "", i, argv[i]);
						}
					}
					else {
						if (szPrevOption.empty()) {
							throw ExceptionBuilder().Build(ExceptionTypes().INVALID_ARGUMENT(), "invalid placement for positional argument '" + std::string(argv[i]) + "'", Severity().CRITICAL());
						}
						else {
							if (StringUtilities().startsWith(szPrevOption, "--")) {
								if (!SetOptionVerbose(szPrevOption, argv[i])) {
									unregistered->RegisterStringOption(szPrevOption, "", -1, argv[i]);
								}
							}
							else {
								if (!SetOptionAbbr(szPrevOption, argv[i])) {
									unregistered->RegisterStringOption("", szPrevOption, -1, argv[i]);
								}
							}
							szPrevOption = "";
						}
					}
				}
			}
			if (!szPrevOption.empty()) {
				if (StringUtilities().startsWith(szPrevOption, "--")) {
					if (!SetFlagVerbose(szPrevOption)) {
						unregistered->RegisterBooleanOption(szPrevOption, "", -1, true);
					}
				}
				else {
					if (!SetFlagAbbr(szPrevOption)) {
						unregistered->RegisterBooleanOption("", szPrevOption, -1, true);
					}
				}
			}
		}
		return unregistered;
	}
	bool SetFlagVerbose(const std::string& szOption) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto it = std::find_if(m_options.begin(), m_options.end(), verbose_match);

		if (it != m_options.end()) {
			it->SetFlag(); // may throw Not_Supported
			return true;
		}
		return false;
	}

	bool SetFlagAbbr(const std::string& szOption) {
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };
		auto it = std::find_if(m_options.begin(), m_options.end(), abbr_match);

		if (it != m_options.end()) {
			it->SetFlag(); // may throw Not_Supported
			return true;
		}
		return false;
	}

	bool SetFlagPos(const int32_t& nPos) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };
		auto it = std::find_if(m_options.begin(), m_options.end(), pos_match);

		if (it != m_options.end()) {
			it->SetFlag(); // may throw Not_Supported
			return true;
		}
		return false;
	}
	

	bool SetOptionVerbose(const std::string& szOption, std::string szValue) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto it = std::find_if(m_options.begin(), m_options.end(), verbose_match);

		if (it != m_options.end()) {
			it->SetOption(szValue); // may throw Not_Supported
			return true;
		}
		return false;
	}

	bool SetOptionAbbr(const std::string& szOption, std::string szValue) {
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };
		auto it = std::find_if(m_options.begin(), m_options.end(), abbr_match);

		if (it != m_options.end()) {
			it->SetOption(szValue); // may throw Not_Supported
			return true;
		}
		return false;
	}

	bool SetOptionPos(const int32_t& nPos, std::string szValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };
		auto it = std::find_if(m_options.begin(), m_options.end(), pos_match);

		if (it != m_options.end()) {
			it->SetOption(szValue); // may throw Not_Supported
			return true;
		}
		return false;
	}

	uint32_t Size() {
		return m_options.size();
	}

	bool TryGetBooleanOption(const std::string& szOption, bool defaultValue, bool verbose = false) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };

		std::vector<clOption>::iterator it;
		if (verbose) {
			it = std::find_if(m_options.begin(), m_options.end(), verbose_match);
		}
		else {
			it = std::find_if(m_options.begin(), m_options.end(), abbr_match);
		}

		if (it != m_options.end()) {
			bool out = defaultValue;
			if (it->GetBooleanOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	bool TryGetBooleanOption(const int32_t nPos, bool defaultValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), pos_match);
		if (it != m_options.end()) {
			bool out = defaultValue;
			if (it->GetBooleanOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	bool TryGetBooleanOption(clOption option, bool defaultValue) {
		auto match = [option](clOption& clOp) { return clOp.MatchAny(option); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), match);

		if (it != m_options.end()) {
			bool out = defaultValue;
			if (it->GetBooleanOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	int32_t TryGetIntegerOption(const std::string& szOption, bool defaultValue, bool verbose = false) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };

		std::vector<clOption>::iterator it;
		if (verbose) {
			it = std::find_if(m_options.begin(), m_options.end(), verbose_match);
		}
		else {
			it = std::find_if(m_options.begin(), m_options.end(), abbr_match);
		}

		if (it != m_options.end()) {
			int32_t out = defaultValue;
			if (it->GetIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	int32_t TryGetIntegerOption(const int32_t nPos, int32_t defaultValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), pos_match);
		if (it != m_options.end()) {
			int32_t out = defaultValue;
			if (it->GetIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	int32_t TryGetIntegerOption(clOption option, int32_t defaultValue) {
		auto match = [option](clOption& clOp) { return clOp.MatchAny(option); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), match);

		if (it != m_options.end()) {
			int32_t out = defaultValue;
			if (it->GetIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	uint32_t TryGetUnsignedIntegerOption(const std::string& szOption, bool defaultValue, bool verbose = false) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };

		std::vector<clOption>::iterator it;
		if (verbose) {
			it = std::find_if(m_options.begin(), m_options.end(), verbose_match);
		}
		else {
			it = std::find_if(m_options.begin(), m_options.end(), abbr_match);
		}

		if (it != m_options.end()) {
			uint32_t out = defaultValue;
			if (it->GetUnsignedIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	uint32_t TryGetUnsignedIntegerOption(const int32_t nPos, uint32_t defaultValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), pos_match);
		if (it != m_options.end()) {
			uint32_t out = defaultValue;
			if (it->GetUnsignedIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	uint32_t TryGetUnsignedIntegerOption(clOption option, uint32_t defaultValue) {
		auto match = [option](clOption& clOp) { return clOp.MatchAny(option); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), match);

		if (it != m_options.end()) {
			uint32_t out = defaultValue;
			if (it->GetUnsignedIntegerOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	std::string TryGetStringOption(const std::string& szOption, std::string defaultValue, bool verbose = false) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };

		std::vector<clOption>::iterator it;
		if (verbose) {
			it = std::find_if(m_options.begin(), m_options.end(), verbose_match);
		}
		else {
			it = std::find_if(m_options.begin(), m_options.end(), abbr_match);
		}

		if (it != m_options.end()) {
			std::string out = defaultValue;
			if (it->GetStringOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	std::string TryGetStringOption(const int32_t nPos, std::string defaultValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), pos_match);
		if (it != m_options.end()) {
			std::string out = defaultValue;
			if (it->GetStringOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	std::string TryGetStringOption(clOption option, std::string defaultValue) {
		auto match = [option](clOption& clOp) { return clOp.MatchAny(option); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), match);

		if (it != m_options.end()) {
			std::string out = defaultValue;
			if (it->GetStringOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}


	bool TryGetDoubleOption(const std::string& szOption, double defaultValue, bool verbose = false) {
		auto verbose_match = [szOption](clOption& clOp) { return clOp.MatchVerbose(szOption); };
		auto abbr_match = [szOption](clOption& clOp) { return clOp.MatchAbbr(szOption); };

		std::vector<clOption>::iterator it;
		if (verbose) {
			it = std::find_if(m_options.begin(), m_options.end(), verbose_match);
		}
		else {
			it = std::find_if(m_options.begin(), m_options.end(), abbr_match);
		}

		if (it != m_options.end()) {
			double out = defaultValue;
			if (it->GetDoubleOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	bool TryGetDoubleOption(const int32_t nPos, double defaultValue) {
		auto pos_match = [nPos](clOption& clOp) { return clOp.MatchPos(nPos); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), pos_match);
		if (it != m_options.end()) {
			double out = defaultValue;
			if (it->GetDoubleOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}

	double TryGetDoubleOption(clOption option, double defaultValue) {
		auto match = [option](clOption& clOp) { return clOp.MatchAny(option); };

		std::vector<clOption>::iterator it = std::find_if(m_options.begin(), m_options.end(), match);

		if (it != m_options.end()) {
			double out = defaultValue;
			if (it->GetDoubleOption(out)) {
				return out;
			}
			return defaultValue;
		}
		return defaultValue;
	}


	_clArgs& RegisterBooleanOption(const std::string& szVerbose, const std::string& szAbbr, uint32_t nPos, bool defaultValue = false) {
		clOptionIdentifier id(szVerbose, szAbbr, nPos);
		clOptionValue value(clOptionType::BOOLEAN, defaultValue);
		m_options.push_back(clOption(id, value));
		return *this;
	}

	_clArgs& RegisterIntegerOption(const std::string& szVerbose, const std::string& szAbbr, uint32_t nPos, int32_t defaultValue = 0) {
		clOptionIdentifier id(szVerbose, szAbbr, nPos);
		clOptionValue value(clOptionType::INT32, defaultValue);
		m_options.push_back(clOption(id, value));
		return *this;
	}

	_clArgs& RegisterUnsignedIntegerOption(const std::string& szVerbose, const std::string& szAbbr, uint32_t nPos, uint32_t defaultValue = 0u) {
		clOptionIdentifier id(szVerbose, szAbbr, nPos);
		clOptionValue value(clOptionType::UINT32, defaultValue);
		m_options.push_back(clOption(id, value));
		return *this;
	}

	_clArgs& RegisterStringOption(const std::string& szVerbose, const std::string& szAbbr, uint32_t nPos, std::string defaultValue = "") {
		clOptionIdentifier id(szVerbose, szAbbr, nPos);
		clOptionValue value(clOptionType::STRING, defaultValue);
		m_options.push_back(clOption(id, value));
		return *this;
	}

private:
	std::vector<clOption> m_options;
};
