#pragma once
#include <map>
#include <string>
#include <memory>

template <class T>
class ResourceMgr
{
public:
	class ResourcePack
	{
	public:
		bool getResource(const std::string& name, T& resource) const
		{
			auto it = mResources.find(name);
			if (it != mResources.end())
			{
				resource = it->second;
				return true;
			}
			return false;
		}

		void addResource(const std::string& name, const T& res)
		{
			mResources.insert(std::make_pair(name, res));
		}

	private:
		std::map<std::string, T> mResources;
	};
	typedef std::shared_ptr<ResourcePack> ResourcePackPtr;

public:

	void addPack(const std::string& packName, const ResourcePackPtr& pack)
	{
		mPacks.insert(std::make_pair(packName, pack));
	}

	bool removePack(const std::string& packName)
	{
		auto it = mPacks.find(packName);
		if (it == mPacks.end()) { return false; }
		mPacks.erase(it);
		return true;
	}

	bool getResource(const std::string& name, T& resource)
	{
		auto it = mPacks.begin();
		const auto itEnd = mPacks.end();
		while (it != itEnd)
		{
			if (it->second->getResource(name, resource))
			{
				return true;
			}
			++it;
		}
		return false;
	}

private:
	std::map<std::string, ResourcePackPtr> mPacks;
};
