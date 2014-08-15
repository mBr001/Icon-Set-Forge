#ifndef ICON_H
#define ICON_H

#include <QImage>
#include <QVector>
#include <memory>
#include "model/iconclassification.h"
#include "model/iconcomponent.h"

/*!
 * Describes a single icon.
 * Includes both the image itself as well as pointers to associated
 * classifications.
 */
class Icon : public IconComponent
{
private:
    //! The image data of the Icon
    QImage image;
    /*!
     * Holds a list of all IconClassifications this Icon applies to.
     * Ownership between the IconClassification is shared between respective
     * parent and this Icon instance. Therefore std::shared_ptr is used.
     */
    QVector<std::shared_ptr<IconClassification>> classifications;
    //! Stores a link to another Icon instance for representing linked icons
    Icon* link;
public:
    Icon();
    Icon(QImage image);
    /*!
     * Assigns this Icon to the specified IconClassification.
     * This function is to be used upon scanning an IconSet, but <b>not</b>
     * for inserting an Icon into a new IconClassification.
     * Use Icon::insertIntoClassification() instead, as otherwise the
     * InsertCommands will not be performed on the Icon which will result
     * in Icons that do not meet the IconClassification's requirements.
     * E.g. a 128x128 pixel Icon in the 24x24 resolution IconClassification.
     * Moreover a check for possible conflicts is done beforehand.
     * \sa IconClassification::isConflicting()
     * \param classification
     * \sa Icon::insertIntoClassification()
     */
    Icon(Icon *linkTo);
    bool addClassification(std::shared_ptr<IconClassification> newClassification);
    /*!
     * Assigns this Icon to the specified IconClassification and performs the
     * chain of InsertCommands defined by the IconClassification.
     * Use this function for inserting new Icons or moving/copying existing
     * Icons into another IconClassification.
     * Moreover a check for possible conflicts is done beforehand.
     * \sa IconClassification::isConflicting()
     * \param classification
     * \return Whether or not the assignment was successful.
     */
    bool insertIntoClassification(
            std::shared_ptr<IconClassification> classification);
    /*!
     * Returns whether the Icon is of type "link" or provides own image data.
     * \return true if link; false if it has an own QImage
     */
    bool isOfLinkType() const;
    //! Returns an QImage that can be used for displaying this particular Icon
    const QImage &getRepresentativeImage() const;
};

#endif // ICON_H
