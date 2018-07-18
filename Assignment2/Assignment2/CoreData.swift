//
//  CoreData.swift
//  Assignment2
//
//  Created by Sean Mitchell on 06/12/2017.
//  Copyright © 2017 Sean Mitchell. All rights reserved.
//

import CoreData

struct CoreData {
    static let shared = CoreData()
    
    //Creates a persistant store to use core data
    let persistantContainer: NSPersistentContainer = {
        let container = NSPersistentContainer(name: "Assignment2")
        container.loadPersistentStores(completionHandler: {(storeDescription, err) in
            if let err = err{
                fatalError("\(err)")
            }
        })
        return container
    }()
    
    //Returns an array of all artworks
    func fetchArtwork() -> [Artwork] {
        let context = persistantContainer.viewContext
        let fetchRequest = NSFetchRequest<Artwork>(entityName: "Artwork")
        do {
            let artwork = try context.fetch(fetchRequest)
            return artwork
        } catch let error{
            print(error)
            return []
        }
    }
    
    //Creates and saves an artwork using the given data
    func saveArtwork(artist: String, distance: Double, enabled: Int, fileName: String, id: Int, information: String, lastModified: String, lat: Double, location: String, locationNotes: String, long: Double, title: String, yearOfWork: String) {
        let context = persistantContainer.viewContext
        let artwork = NSEntityDescription.insertNewObject(forEntityName: "Artwork", into: context) as! Artwork
        artwork.setValue(artist, forKey: "artist")
        artwork.setValue(distance, forKey: "distance")
        artwork.setValue(enabled, forKey: "enabled")
        artwork.setValue(fileName, forKey: "fileName")
        artwork.setValue(id, forKey: "id")
        artwork.setValue(information, forKey: "information")
        artwork.setValue(lastModified, forKey: "lastModified")
        artwork.setValue(lat, forKey: "lat")
        artwork.setValue(location, forKey: "location")
        artwork.setValue(locationNotes, forKey: "locationNotes")
        artwork.setValue(long, forKey: "long")
        artwork.setValue(title, forKey: "title")
        artwork.setValue(yearOfWork, forKey: "yearOfWork")
        do {
            try context.save()
        } catch let error{
            print(error)
        }
    }
    
    //Return whether or not an artwork with a given id is saved in core data
    func findArtwork(id: Int) -> Bool {
        let artworks = fetchArtwork()
        let count = artworks.count
        if count == 0 {
            return false
        }
        
        for index in 0...count-1{
            let artwork = artworks[index]
            if artwork.id == id {
                return true
            }
        }
        return false
    }
}

