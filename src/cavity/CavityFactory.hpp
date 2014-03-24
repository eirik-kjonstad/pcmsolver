#ifndef CAVITYFACTORY_HPP
#define CAVITYFACTORY_HPP

#include <map>
#include <string>

#include "Config.hpp"


class Cavity;
struct cavityData;

/*!
 *	\file CavityFactory.hpp
 *	\class CavityFactory
 *	\brief Implementation of the Factory Method for cavities.
 *	\author Roberto Di Remigio
 *	\date 2013
 *
 * 	Factory method implementation shamelessly copied from "Modern C++ Design" of A. Alexandrescu.
 * 	It is implemented as a Singleton.
 */

class CavityFactory
{
public:
    /*!
     * Callback function for cavity creation.
     */
    typedef Cavity * (*createCavityCallback)(const cavityData & _data);
private:
    /*!
     * A map from the cavity type identifier (a string) to its callback function.
     */
    typedef std::map<std::string, createCavityCallback> CallbackMap;
public:
    /*!
     * \brief Returns true if registration of the cavityID was successful
     * \param cavityID the cavity identification string
     * \param createFunction the creation function related to the cavity type given
     */
    bool registerCavity(std::string cavityID, createCavityCallback createFunction);
    /*!
     * \brief Returns true if cavityID was already registered
     * \param cavityID the cavity identification string
     */
    bool unRegisterCavity(std::string cavityID);
    /*!
     * Calls the appropriate creation function, based on the passed cavityID
     */
    Cavity * createCavity(std::string cavityID, const cavityData & _data);
    /*!
     * Unique point of access to the unique instance of the CavityFactory
     */
    static CavityFactory& TheCavityFactory() {
        static CavityFactory obj;
        return obj;
    }
private:
    CavityFactory() {}
    /// Copy constructor is made private
    CavityFactory(const CavityFactory &other);
    CavityFactory& operator=(const CavityFactory &other);
    ~CavityFactory() {}
    CallbackMap callbacks;
};

#endif // CAVITYFACTORY_HPP
