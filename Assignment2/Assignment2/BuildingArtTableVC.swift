//
//  BuildingArtTableVC.swift
//  Assignment2
//
//  Created by Sean Mitchell on 08/12/2017.
//  Copyright © 2017 Sean Mitchell. All rights reserved.
//

import UIKit

class BuildingArtTableVC: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    override func viewDidLoad() {
        super.viewDidLoad()     
    }
    
    //Works out the number of artworks in the bulding (And therefor number of rows)
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        var artworkCount = 0
        artworks.forEach{(artwork) in
            if artwork.location == artworkBuildings[currentBuildingIndex]{
                artworkCount+=1
            }
        }
        return artworkCount
    }
    
    //Adds the artwork data to the table, all from the current building
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cellCount = 0
        let cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "Cell")
        artworks.forEach{(artwork) in
            if artwork.location == artworkBuildings[currentBuildingIndex] && cellCount <= indexPath.row{
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
            if artwork.location == artworkBuildings[currentBuildingIndex] && cellCount <= indexPath.row{
                currentArtIndex = artIndex
                cellCount+=1
            }
            artIndex+=1
        }
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let artworkInfoVC = storyboard.instantiateViewController(withIdentifier: "ArtworkInfoVC") as! ArtworkInfoVC
        self.present(artworkInfoVC, animated: true, completion: nil)
    }
    
    //Navigates back to the main page
    @IBAction func backBttnAIClick(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var backBttnBA: UIButton!
}

