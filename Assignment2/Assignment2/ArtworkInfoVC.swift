//
//  ArtworkInfoVC.swift
//  Assignment2
//
//  Created by Sean Mitchell on 08/12/2017.
//  Copyright © 2017 Sean Mitchell. All rights reserved.
//

import UIKit

class ArtworkInfoVC: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //Retreives and displays all the artworks information
        let artworkImage = artworkImages[artworks[currentArtIndex].fileName!]
        imageViewAI.image = artworkImage
        titleLblAI.text = artworks[currentArtIndex].title
        artistLblAI.text = "Created by " + artworks[currentArtIndex].artist! + " in " + artworks[currentArtIndex].yearOfWork!
        infoLblAI.text = artworks[currentArtIndex].information
        locationLblAI.text = artworks[currentArtIndex].locationNotes
        
    }
    
    //Navigates back to the main page
    @IBAction func backBttnAIClick(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBOutlet weak var backBttnAI: UIButton!
    @IBOutlet weak var imageViewAI: UIImageView!
    @IBOutlet weak var artistLblAI: UILabel!
    @IBOutlet weak var titleLblAI: UILabel!
    @IBOutlet weak var infoLblAI: UILabel!
    @IBOutlet weak var locationLblAI: UILabel!
}
