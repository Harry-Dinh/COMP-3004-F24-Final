#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QString>
#include <QDateTime>
#include <vector>

using namespace std;

/**
 * @brief A class containing the data for one measurement that stores the values of the 24 meridian points on the body, as well as the ID of the user who took the measurement and the time that was taken.
 */
class Measurement {
    private:
        /// @brief References the user taking this measurement
        int userID;
        
        /// @brief The date/time that this measurement was created
        QString timeRecorded;
        
        /// @brief An array storing 24 meridian values
        QVector<double> meridianValues;
        
    public:
        
        // CONSTRUCTORS
        
        /// @brief Creation constructor, **Use this for creating a new measurement.**
        Measurement(int userID, QDateTime& timeRecorded);
        
        /// @brief Exisitng constructor, **Use this to load existing data into memory**, like loading history data.
        Measurement(int userID, QDateTime& timeRecorded, QVector<double> meridianValues);
        
        // GETTERS
        
        /**
         * @brief Return the user ID
         */
        int getUserID() const;
        
        /**
         * @brief Return the time recorded in `QString` form
         */
        QString getTimeRecorded();
        
        /**
         * @brief Return the entire array of meridian values
         */
        QVector<double> getValues();
        
        /**
         * @brief Return a single meridian value inside the array.
         * @param index the index to look for in the array
         * @return This function returns -1 if the provided index is out of bounds or the array is empty. Otherwise, it will return the value at the specified index.
         */
        double getValue(int index) const;
        
        // SETTERS
        
        /**
         * @brief Setter for the user ID
         * @param userID the new ID to assign
         */
        void setUserID(int userID);
        
        /**
         * @brief Setter for the time recorded
         * @param timeRecorded the new `QDateTime` object to record the time, then converted to `QString` before assigning
         */
        void setTimeRecorded(QDateTime& timeRecorded);
        
        /**
         * @brief Setter for the meridian array
         * @param src The data source to assign
         */
        void setArray(QVector<double> src);
        
        /**
         * @brief Add an existing value to the meridian array
         * @param existingValue the existing value to add
         */
        void addExistingValue(double existingValue);
        
        /**
         * @brief Generate a random number then add it to the back of the array
         * **This function should be called whenever the user presses the "Take Measurement" button!**
         */
        void generateValue();
        
        /**
         * @brief Return one of the 3 strings: Hyperactive (above established bound), Balanced (within established bound), and Hypoactive (below established bound)
         * @param value the meridian value to interpret
         */
        string interpretValue(double value);
};

#endif // MEASUREMENT_H
