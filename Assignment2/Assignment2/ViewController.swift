//
//  ViewController.swift
//  Assignment2
//
//  Created by Sean Mitchell on 06/12/2017.
//  Copyright © 2017 Sean Mitchell. All rights reserved.
//

import UIKit
import MapKit

//global variables describing the artworks and the resources for manipulating them
var currentPlace = -1
var currentArtIndex = -1
var currentBuildingIndex = -1
var artworkImages = Dictionary<String, UIImage>()
var artworks = [Artwork]()
var artworkBuildings = [String]()

class ViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate, UITableViewDelegate, UITableViewDataSource {
    
    var locationManager = CLLocationManager()
    
    //Structures defining the artwork and the Json file containing them
    private struct artworks2Struct: Decodable{
        let id: String
        let title: String
        let artist: String
        let yearOfWork: String
        let Information: String
        let lat: String
        let long: String
        let location: String
        let locationNotes: String
        let fileName: String
        let lastModified: String
        let enabled: String
    }
    
    private struct artworksStruct: Decodable{
        let artworks2: [artworks2Struct]
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        //centre the map on the user's location
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
        
        //Retreive the Json file for adding any new entries, and setting up the map and table
        self.getJsonData()
        getArtworkDistanceOrder()
        tableView.reloadData()
        getArtworkBuildings()
        getArtworkImages()
        populateMap()
    }
    
    //Retreives Json data from the internet
    private func getJsonData(){
        let jsonUrlString = "https://cgi.csc.liv.ac.uk/~phil/Teaching/COMP327/artworksOnCampus/data.php?class=artworks2&lastUpdate=2017-11-01"
        //If the URL cannot be created, return
        guard let jsonUrl = URL(string: jsonUrlString) else{
            return
        }
        //Retreive Json data from the URL
        URLSession.shared.dataTask(with: jsonUrl) { (data, response, error) in
            if error != nil{
                print("\(String(describing: error))")
                return
            }
            //If there is a problem with the data, return
            //Guards against sudden drop in internet or data loss
            guard let data = data else{
                return
            }
            //Decode Json data and use it
            do {
                let jsonData = try JSONDecoder().decode(artworksStruct.self, from: data)
                self.useJsonData(jsonData: jsonData)
            } catch let jsonError {
                print("error getting json data \(String(describing: jsonError))")
            }
            }.resume() //Resume program functioning
    }
    
    //Creates a duplicate free list of the different buildings that contain artworks
    private func getArtworkBuildings(){
        artworks.forEach{(artwork) in
            if artworkBuildings.contains(artwork.location!) != true {
                artworkBuildings.append(artwork.location!)
            }
        }
    }
    
    //Retreives all artwork images and stores them
    private func getArtworkImages(){
        var index: Int
        index = 0
        //For each artwork,add the file name to the base url string to get the url of the image
        artworks.forEach{(artwork) in
            let imgURLString = "https://cgi.csc.liv.ac.uk/~phil/Teaching/COMP327/artwork_images/" + artwork.fileName!
            let newImgURLString = imgURLString.addingPercentEncoding(withAllowedCharacters: CharacterSet.urlQueryAllowed)
            //If the URL cannot be created, return
            if let url = URL(string: newImgURLString!){
                //Retrive the image from the Url
                URLSession.shared.dataTask(with: url) { data, response, error in
                    if error != nil{
                        print("\(String(describing: error))")
                        return
                    }
                    //If there is a problem with the data, return
                    //Guards against sudden drop in internet or data loss
                    guard let data = data, error == nil else{
                        return
                    }
                    //stores the image
                    artworkImages[artwork.fileName!] = UIImage(data:data)!
                }.resume() //Resume program functioning
            }
            index+=1
        }
    }
    
    //Use the decoded Json file to populate the variables required for program functioning
    private func useJsonData(jsonData: artworksStruct){
        jsonData.artworks2.forEach { (artworks) in
            //Finds current location and works out distance to the artwork
            let currentLocation = CLLocation(latitude: map.userLocation.coordinate.latitude, longitude: map.userLocation.coordinate.longitude)
            let artworkLocation = CLLocation(latitude: Double(artworks.lat)!, longitude: Double(artworks.long)!)
            let totalDistance = Double(currentLocation.distance(from: artworkLocation))
            //If the artwork is not already stored in core data, save it
            if CoreData.shared.findArtwork(id: Int(artworks.id)!) == false {
                let saveArtworks = CoreData()
                saveArtworks.saveArtwork(artist: artworks.artist, distance: totalDistance, enabled: Int(artworks.enabled)!, fileName: artworks.fileName, id: Int(artworks.id)!, information: artworks.Information, lastModified: artworks.lastModified, lat: Double(artworks.lat)!, location: artworks.location, locationNotes: artworks.locationNotes, long: Double(artworks.long)!, title: artworks.title, yearOfWork: artworks.yearOfWork).self
            }
        }
        
    }
    
    //Orders the artworks based upon distance from the user
    private func getArtworkDistanceOrder(){
        var unsortedArtworks = [Artwork]()
        unsortedArtworks = CoreData.shared.fetchArtwork()
        artworks = unsortedArtworks.sorted {(lhs, rhs) in
            return lhs.distance < rhs.distance
        }
    }
    
    //Updates the map to view the current location at an appropriate level
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let location = CLLocationCoordinate2D(latitude: locations[0].coordinate.latitude, longitude: locations[0].coordinate.longitude)
        let span = MKCoordinateSpan(latitudeDelta: 0.002, longitudeDelta: 0.002)
        let region = MKCoordinateRegion(center: location, span: span)
        self.map.setRegion(region, animated: true)
    }
    
    //Titles the group headers in the table
    public func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return artworkBuildings[section]
    }
    
    //Works out the number of artworks in each group (And therefor number of rows)
    public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        var artworkCount = 0
        artworks.forEach{(artwork) in
            if artwork.location == artworkBuildings[section]{
                artworkCount+=1
            }
        }
        return artworkCount
    }
    
    //Number of buildings (Therefor number of sections)
    public func numberOfSections(in tableView: UITableView) -> Int {
        return artworkBuildings.count
    }
    
    //Adds the artwork data to the table, based upon section
    public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cellCount = 0
        let cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "Cell")
        artworks.forEach{(artwork) in
            if artwork.location == artworkBuildings[indexPath.section] && cellCount <= indexPath.row{
                cell.textLabel?.numberOfLines = 0
                cell.textLabel?.text = artwork.title! + ": " + String(round(artwork.distance)) + "m"
                cellCount+=1
            }
        }
        return cell
    }
    
    //Enables the user to click on a table cell to navigate to that artwork
    public func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        var cellCount = 0
        var artIndex = 0
        artworks.forEach{(artwork) in
            if artwork.location == artworkBuildings[indexPath.section] && cellCount <= indexPath.row{
                currentArtIndex = artIndex
                cellCount+=1
            }
            artIndex+=1
        }
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let artworkInfoVC = storyboard.instantiateViewController(withIdentifier: "ArtworkInfoVC") as! ArtworkInfoVC
        self.present(artworkInfoVC, animated: true, completion: nil)
    }
    
    //Populates the mapview with annotations
    public func populateMap(){
        var averageLat: Double = 0
        var averageLong: Double = 0
        var numberOfArtworks: Double = 0
        //Count number of artworks in each building and average the distances to artworks in the same building
        //This allows for a single annotation for buildings with many artworks
        artworkBuildings.forEach{(building) in
            artworks.forEach{(artwork) in
                if artwork.location == building{
                    numberOfArtworks+=1
                    averageLat = averageLat + artwork.lat
                    averageLong = averageLong + artwork.long
                }
            }
            averageLat = averageLat / numberOfArtworks
            averageLong = averageLong / numberOfArtworks
            //If the artwork is the only one in its building
            if numberOfArtworks == 1{
                addArtworkAnnotation(building: building)
            } else{ //If there are multiple artworks in one building
                addBuildingAnnotation(building: building, lat: averageLat, long: averageLong)
            }
            numberOfArtworks = 0
            averageLat = 0
            averageLong = 0
        }
    }
    
    //Adds an annotation for a single artwork
    public func addArtworkAnnotation(building: String){
        artworks.forEach{(artwork) in
            if artwork.location == building{
                let annotation = PinAnnotation()
                annotation.setCoordinate(newCoordinate: CLLocationCoordinate2D(latitude: artwork.lat, longitude: artwork.long))
                annotation.setTitle(newTitle: artwork.title!)
                self.map.addAnnotation(annotation)
            }
        }
    }
    
    //Adds an annotation for a building with multiple artworks
    public func addBuildingAnnotation(building: String, lat: Double, long: Double){
        let annotation = PinAnnotation()
        annotation.setCoordinate(newCoordinate: CLLocationCoordinate2D(latitude: lat, longitude: long))
        annotation.setTitle(newTitle: building)
        self.map.addAnnotation(annotation)
    }
    
    //Custom annotation class that allows for custom annotation view and clicking
    class PinAnnotation : NSObject, MKAnnotation {
        private var coord: CLLocationCoordinate2D = CLLocationCoordinate2D(latitude: 0, longitude: 0)
        var title: String?
        var coordinate: CLLocationCoordinate2D {
            get {
                return coord
            }
        }
        
        func setCoordinate(newCoordinate: CLLocationCoordinate2D){
            self.coord = newCoordinate
        }
        
        func setTitle(newTitle: String){
            title = newTitle
        }
    }
    
    //Displays each annotations annotation view, and adds an info button to allow navigation
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        if annotation is MKUserLocation{
            return nil;
        }else{
            let pinAnnotationView = MKPinAnnotationView(annotation: annotation, reuseIdentifier: "myPin")
            
            pinAnnotationView.isDraggable = true
            pinAnnotationView.canShowCallout = true
            pinAnnotationView.animatesDrop = true
            
            let calloutButton = UIButton(type: .detailDisclosure)
            pinAnnotationView.rightCalloutAccessoryView = calloutButton
            pinAnnotationView.sizeToFit()
            
            return pinAnnotationView
        }
    }
    
    //Allows detection of when the annotation info button is clicked
    func mapView(_ mapView: MKMapView, annotationView view: MKAnnotationView, calloutAccessoryControlTapped control: UIControl) {
        if control == view.rightCalloutAccessoryView {
            //Determine whether the annotation was for a bulding or a single artwork
            var index = 0
            var isBuilding = false
            artworkBuildings.forEach{(building) in
                if view.annotation!.title! == building{
                    currentBuildingIndex = index
                    isBuilding = true
                }
                index+=1
            }
            //If the annotation was a single artwork, navigate to the artwork info page
            if isBuilding == false{
                index = 0
                artworks.forEach{(artwork) in
                    if artwork.title == view.annotation!.title!{
                        currentArtIndex = index
                    }
                    index+=1
                }
                let storyboard = UIStoryboard(name: "Main", bundle: nil)
                let artworkInfoVC = storyboard.instantiateViewController(withIdentifier: "ArtworkInfoVC") as! ArtworkInfoVC
                self.present(artworkInfoVC, animated: true, completion: nil)
            }else{ //If the annotation is a building, navigate to the building table view
                let storyboard = UIStoryboard(name: "Main", bundle: nil)
                let buildingArtTableVC = storyboard.instantiateViewController(withIdentifier: "BuildingArtTableVC") as! BuildingArtTableVC
                self.present(buildingArtTableVC, animated: true, completion: nil)
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBOutlet weak var map: MKMapView!
    @IBOutlet weak var tableView: UITableView!
}

