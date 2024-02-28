db.sales.insertMany([
    {
        "date": ISODate("2023-10-27T15:45:00Z"),
        "product": "Widget",
        "quantity": 50,
        "price": 10.00
    },
    {
        "date": ISODate("2023-10-28T12:30:00Z"),
        "product": "Gadget",
        "quantity": 80,
        "price": 15.00
    },
    {
        "date": ISODate("2023-10-29T09:15:00Z"),
        "product": "Widget",
        "quantity": 60,
        "price": 10.00
    },
    {
        "date": ISODate("2023-10-30T14:00:00Z"),
        "product": "Gadget",
        "quantity": 70,
        "price": 15.00
    }
])

//index creation
db.sales.createIndex({ "date": 1, "product": 1 })



//view index
db.sales.getIndexes()


// aggregation
db.sales.aggregate([
    {
        $match: {
            date: {
                $gte: ISODate("2023-10-01T00:00:00Z"),
                $lte: ISODate("2023-10-31T23:59:59Z")
            }
        }
    },
    {
        $group: {
            _id: "$product",
            totalRevenue: { $sum: { $multiply: ["$quantity", "$price"] } }
        }
    },
    {
        $sort: { totalRevenue: -1 }
    },
    {
        $project: {
            _id: 0,
            product: "$_id",
            totalRevenue: 1
        }
    }
])


db.sales.aggregate([
    {
        $match: {
            date: {
                $gte: ISODate("2023-10-01T00:00:00Z"),
                $lte: ISODate("2023-10-31T23:59:59Z")
            }
        }
    },
    {
        $group: {
            _id: "$product",
            totalRevenue: { $sum: { $multiply: ["$quantity", "$price"] } }
        }
    },
    {
        $sort: { totalRevenue: -1 }
    },
    {
        $limit:1
    }
])
