#pragma once

class ResourceBase {
public:
	ResourceBase() = default;
	virtual ~ResourceBase() = default;
public:
	void SetKey(const wstring& key) { m_strKey = key; }
	void SetPath(const wstring& path) { m_strRelativePath = path; }
	const wstring& GetKey() const { return m_strKey; }
	const wstring& GetPath() const { return m_strRelativePath; }
private:
	wstring m_strRelativePath;
	wstring m_strKey;
};

